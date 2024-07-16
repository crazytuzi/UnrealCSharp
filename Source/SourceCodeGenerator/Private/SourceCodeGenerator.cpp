#include "SourceCodeGenerator.h"
#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "FSourceCodeGeneratorModule"

void FSourceCodeGeneratorModule::StartupModule()
{
	IModularFeatures::Get().RegisterModularFeature(TEXT("ScriptGenerator"), this);
}

void FSourceCodeGeneratorModule::ShutdownModule()
{
	IModularFeatures::Get().UnregisterModularFeature(TEXT("ScriptGenerator"), this);
}

FString FSourceCodeGeneratorModule::GetGeneratedCodeModuleName() const
{
	return TEXT("UnrealCSharp");
}

bool FSourceCodeGeneratorModule::SupportsTarget(const FString& TargetName) const
{
	const auto SettingFile = FPaths::Combine(
		FPaths::ConvertRelativePathToFull(FPaths::GetPath(FPaths::GetProjectFilePath())),
		TEXT("Config/DefaultUnrealCSharpEditorSetting.ini"));

	auto bEnableExport = false;

	if (FPaths::FileExists(SettingFile))
	{
		GConfig->GetBool(
			TEXT("/Script/UnrealCSharpCore.UnrealCSharpEditorSetting"),
			TEXT("bEnableExport"),
			bEnableExport,
			SettingFile);
	}

	return bEnableExport;
}

bool FSourceCodeGeneratorModule::ShouldExportClassesForModule(const FString& ModuleName,
                                                              EBuildModuleType::Type ModuleType,
                                                              const FString& ModuleGeneratedIncludeDirectory) const
{
	return ExportModules.Contains(ModuleName) &&
		(ModuleType == EBuildModuleType::EngineRuntime || ModuleType == EBuildModuleType::GameRuntime);
}

void FSourceCodeGeneratorModule::Initialize(const FString& RootLocalPath, const FString& RootBuildPath,
                                            const FString& OutputDirectory, const FString& IncludeBase)
{
	OutputDir = FPaths::Combine(OutputDirectory, TEXT("UHT/"));

	const auto ProjectPath = FPaths::ConvertRelativePathToFull(FPaths::GetPath(FPaths::GetProjectFilePath()));

	const auto ProjectSourcePath = FPaths::Combine(ProjectPath, TEXT("Source/"));

	const auto ProjectPluginsPath = FPaths::Combine(ProjectPath, TEXT("Plugins/"));

	const auto EngineSourcePath = FPaths::EngineSourceDir();

	const auto EnginePluginsPath = FPaths::EnginePluginsDir();

	const auto ConfigFilePath = FPaths::Combine(ProjectPath, TEXT("Config/DefaultUnrealCSharpEditorSetting.ini"));

	const auto ConfigSection = FString(TEXT("/Script/UnrealCSharpCore.UnrealCSharpEditorSetting"));

	GetModules(ProjectSourcePath, Project);

	GetModules(ProjectSourcePath, HeaderPath);

	GetModules(ProjectPluginsPath, HeaderPath);

	GetPlugins(ProjectPluginsPath, HeaderPath);

	GetModules(FPaths::Combine(EngineSourcePath, TEXT("Developer/")), HeaderPath);

	GetModules(FPaths::Combine(EngineSourcePath, TEXT("Editor/")), HeaderPath);

	GetModules(FPaths::Combine(EngineSourcePath, TEXT("Programs/")), HeaderPath);

	GetModules(FPaths::Combine(EngineSourcePath, TEXT("Runtime/")), HeaderPath);

	GetModules(EnginePluginsPath, HeaderPath);

	GetPlugins(EnginePluginsPath, HeaderPath);

	if (FPaths::FileExists(ConfigFilePath))
	{
		GConfig->GetArray(*ConfigSection, TEXT("+ExportModule"), ExportModules, ConfigFilePath);
	}
}

void FSourceCodeGeneratorModule::ExportProperty(FBigStringBuilder& StringBuilder,
                                                const UClass* Class,
                                                const FProperty* Property)
{
	StringBuilder.Appendf(TEXT(
		"\t\t\t.Property(\"%s\", BINDING_PROPERTY(&%s::%s))\r\n"
	),
	                      *Property->GetNameCPP(),
	                      *(Class->GetPrefixCPP() + Class->GetName()),
	                      *Property->GetNameCPP());
}

void FSourceCodeGeneratorModule::ExportFunction(FBigStringBuilder& StringBuilder,
                                                const UClass* Class,
                                                const UFunction* Function)
{
	StringBuilder.Appendf(TEXT(
		"\t\t\t.Function(\"%s\", BINDING_OVERLOAD(%s, &%s::%s"
		),
			*Function->GetName(),
			*GetFunctionSignature(Class, Function),
			*(Class->GetPrefixCPP() + Class->GetName()),
			*Function->GetName());

	bool bHasParameters = false;

	for (TFieldIterator<FProperty> It(Function); It; ++It)
	{
		if (It->HasAnyPropertyFlags(CPF_Parm) && !It->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			bHasParameters = true;
			
			break;
		}
	}

	if (bHasParameters)
	{
		StringBuilder.Append(FString::Printf(TEXT(", %s"), *GetFunctionParamName(Function)));
	}

	if (!Function->HasAnyFunctionFlags(FUNC_Static))
	{
		StringBuilder.Append(TEXT(", EFunctionInteract::Virtual"));
	}

	if (bHasParameters)
	{
		StringBuilder.Append(GetFunctionDefaultValue(Function));
	}

	StringBuilder.Append("))\r\n");
}

void FSourceCodeGeneratorModule::ExportClass(UClass* Class, const FString& SourceHeaderFilename,
	const FString& GeneratedHeaderFilename,bool bHasChanged)
{
	if (CanExportClass(Class))
	{
		TSet<UClass*> DependencyClasses = {Class};

		FBigStringBuilder StringBuilder;

		FBigStringBuilder BodyBuilder;

		StringBuilder.Append(TEXT(
			"#pragma once\r\n\r\n"
			"PRAGMA_DISABLE_DEPRECATION_WARNINGS\r\n\r\n"));

		BodyBuilder.Appendf(TEXT(
			"struct FRegister%s\r\n"
			"{\r\n"
			"\tFRegister%s()\r\n"
			"\t{\r\n"
			"\t\tTBindingClassBuilder<%s>(NAMESPACE_BINDING)\r\n"
		),
		                                   *Class->GetName(),
		                                   *Class->GetName(),
		                                   *(Class->GetPrefixCPP() + Class->GetName())
		);

		for (TFieldIterator<FProperty> Property(Class, EFieldIterationFlags::None); Property; ++Property)
		{
			if (CanExportProperty(*Property))
			{
				GetDependencyClasses(*Property, DependencyClasses);

				ExportProperty(BodyBuilder, Class, *Property);
			}
		}

		for (TFieldIterator<UFunction> Function(Class, EFieldIterationFlags::None); Function; ++Function)
		{
			if (CanExportFunction(*Function))
			{
				for (TFieldIterator<FProperty> Property(*Function); Property; ++Property)
				{
					GetDependencyClasses(*Property, DependencyClasses);
				}

				ExportFunction(BodyBuilder, Class, *Function);
			}
		}

		for (const auto DependencyClass : DependencyClasses)
		{
			StringBuilder.Append(GetInclude(DependencyClass));
		}

		StringBuilder.Append("\r\n");

		BodyBuilder.RemoveSuffix(2);

		BodyBuilder.Appendf(TEXT(
			";\r\n"
			"\t}\r\n"
			"};\r\n"
			"\r\n"
			"static FRegister%s Register%s;\r\n\r\n"
		),
		                                   *Class->GetName(),
		                                   *Class->GetName()
		);

		ModuleHeaderPath.FindOrAdd(
			FPaths::GetCleanFilename(Class->GetPackage()->GetName())).Add(*Class->GetName() + BindingSuffix);

		StringBuilder.Append(BodyBuilder);

		StringBuilder.Append(
			"PRAGMA_ENABLE_DEPRECATION_WARNINGS\r\n");

		const FString FilePath = FString::Printf(
			TEXT("%s"), *FPaths::Combine(OutputDir, *Class->GetName() + BindingSuffix));

		SaveIfChanged(*FilePath, StringBuilder.ToString());
	}
}

void FSourceCodeGeneratorModule::FinishExport()
{
	for (const auto& HeaderIt : ModuleHeaderPath)
	{
		FString FileContent;

		const FString FilePath = FString::Printf(
			TEXT("%s"), *FPaths::Combine(OutputDir, *HeaderIt.Key + HeaderSuffix));

		for (const auto& BindingName : HeaderIt.Value)
		{
			FileContent.Append(FString::Printf(TEXT(
				"#include \"%s\"\n"
			),
			                                   *BindingName
			));
		}

		SaveIfChanged(*FilePath, FileContent);
	}
}

FString FSourceCodeGeneratorModule::GetGeneratorName() const
{
	return TEXT("UnrealCSharp Script Generator");
}

bool FSourceCodeGeneratorModule::CanExportClass(const UClass* Class)
{
	return !Class->HasAnyClassFlags(CLASS_Interface) &&
		IsClassTypeSupported(Class);
}

bool FSourceCodeGeneratorModule::CanExportFunction(const UFunction* Function)
{
	if (Function->GetOwnerClass() != nullptr)
	{
		if (!Function->GetOwnerClass()->HasAnyClassFlags(CLASS_RequiredAPI) &&
			!Function->HasAnyFunctionFlags(FUNC_RequiredAPI))
		{
			return false;
		}
	}

	if (Function->HasAnyFunctionFlags(FUNC_Delegate | FUNC_MulticastDelegate))
	{
		return false;
	}

	if (!Function->HasAnyFunctionFlags(FUNC_Public))
	{
		return false;
	}

	if (Function->HasAnyFunctionFlags(FUNC_EditorOnly))
	{
		return false;
	}

	if (Function->HasMetaData(FName("CustomThunk")))
	{
		return false;
	}

	if (const auto ReturnProperty = Function->GetReturnProperty())
	{
		if (ReturnProperty->IsA<FMapProperty>())
		{
			return false;
		}
	}

	for (TFieldIterator<FProperty> It(Function); It; ++It)
	{
		if (!IsPropertyTypeSupported(*It))
		{
			return false;
		}
	}

	return true;
}

bool FSourceCodeGeneratorModule::CanExportProperty(const FProperty* Property)
{
	return !Property->HasAnyPropertyFlags(CPF_EditorOnly) &&
		Property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPublic) &&
		IsPropertyTypeSupported(Property);
}

bool FSourceCodeGeneratorModule::IsClassTypeSupported(const UClass* Class)
{
	return !Class->HasAnyClassFlags(CLASS_Deprecated) &&
	(Class == UObject::StaticClass() ||
		Class->HasAnyClassFlags(CLASS_RequiredAPI | CLASS_MinimalAPI));
}

bool FSourceCodeGeneratorModule::IsPropertyTypeSupported(const FProperty* Property)
{
	if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
	{
		return IsPropertyTypeSupported(ArrayProperty->Inner);
	}

	if (const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
	{
		if (!IsClassTypeSupported(ObjectProperty->PropertyClass))
		{
			return false;
		}
	}

	if (const FObjectPtrProperty* ObjectPtrProperty = CastField<FObjectPtrProperty>(Property))
	{
		if (!IsClassTypeSupported(ObjectPtrProperty->PropertyClass))
		{
			return false;
		}
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		if (InterfaceProperty->InterfaceClass == UInterface::StaticClass())
		{
			return false;
		}
	}

	if (Property->IsA<FEnumProperty>())
	{
		return false;
	}

	if (Property->IsA<FByteProperty>())
	{
		return false;
	}

	if (Property->IsA<FDelegateProperty>())
	{
		return false;
	}

	if (Property->IsA<FMulticastDelegateProperty>())
	{
		return false;
	}

	if (Property->IsA<FFieldPathProperty>())
	{
		return false;
	}

	if (const auto StructProperty = CastField<FStructProperty>(Property))
	{
		if (!StructProperty->HasNoOpConstructor())
		{
			return false;
		}
	}

	bool bIsBitField = false;

	if (const FBoolProperty* BoolProperty = CastField<FBoolProperty>(Property))
	{
		if (!BoolProperty->IsNativeBool())
		{
			bIsBitField = true;
		}
	}

	return !bIsBitField && !(Property->ArrayDim > 1);
}

FString FSourceCodeGeneratorModule::GetReturnPropertySignature(const FProperty* Property)
{
	if (Property == nullptr)
	{
		return TEXT("void");
	}

	FString StringBuilder;

	bool bShouldConst = false;

	if (Property->HasAnyPropertyFlags(CPF_ConstParm) || Property->HasMetaData(FName("NativeConst")))
	{
		StringBuilder.Append(TEXT("const "));

		bShouldConst = true;
	}

	GetPropertySignature(Property, StringBuilder);

	if (Property->IsA<FStrProperty>())
	{
		if (bShouldConst &&
			!Property->HasAnyPropertyFlags(CPF_ConstParm))
		{
			StringBuilder.Append(TEXT("&"));
		}
	}
	else if (Property->HasAnyPropertyFlags(CPF_ReferenceParm) &&
		Property->HasAnyPropertyFlags(CPF_ConstParm))
	{
		StringBuilder.Append(TEXT("&"));
	}

	return StringBuilder;
}

FString FSourceCodeGeneratorModule::GetParamPropertySignature(const FProperty* Property)
{
	if (Property == nullptr)
	{
		return TEXT("void");
	}

	FString SignatureContent;

	bool bShouldConst = false;

	if (Property->HasAnyPropertyFlags(CPF_ConstParm) || Property->HasMetaData(FName("NativeConst")))
	{
		SignatureContent.Append(TEXT("const "));

		bShouldConst = true;
	}

	GetPropertySignature(Property, SignatureContent);

	if (Property->IsA<FStrProperty>())
	{
		if (bShouldConst &&
			!Property->HasAnyPropertyFlags(CPF_ConstParm) ||
			Property->HasAnyPropertyFlags(CPF_OutParm))
		{
			SignatureContent.Append(TEXT("&"));
		}
	}
	else if (Property->HasAnyPropertyFlags(CPF_OutParm) ||
		Property->HasAnyPropertyFlags(CPF_ReferenceParm))
	{
		SignatureContent.Append(TEXT("&"));
	}

	return SignatureContent;
}

FString FSourceCodeGeneratorModule::GetFunctionSignature(const UClass* Class, const UFunction* Function)
{
	FString FunctionContent;

	FunctionContent.Append(GetReturnPropertySignature(Function->GetReturnProperty()));

	if (Function->HasAnyFunctionFlags(FUNC_Static))
	{
		FunctionContent.Append(TEXT("(*)"));
	}
	else
	{
		FunctionContent.Append(FString::Printf(TEXT(
			"(%s::*)"
		),
		                                       *(Class->GetPrefixCPP() + Class->GetName())
		));
	}

	FunctionContent.Append("(");

	bool bIsHasParameter = false;

	for (TFieldIterator<FProperty> PropIt(Function); PropIt; ++PropIt)
	{
		if (!PropIt->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			FunctionContent.Append(GetParamPropertySignature(*PropIt));

			FunctionContent.Append(TEXT(", "));

			bIsHasParameter = true;
		}
	}

	if (bIsHasParameter)
	{
		FunctionContent = FunctionContent.Left(FunctionContent.Len() - 2);
	}

	FunctionContent.Append(TEXT(")"));

	if (Function->HasAnyFunctionFlags(FUNC_Const))
	{
		FunctionContent.Append(TEXT("const"));
	}

	return FunctionContent;
}

FString FSourceCodeGeneratorModule::GetFunctionParamName(const UFunction* Function)
{
	FSmallStringBuilder Builder;

	Builder.Append("TArray<FString>{");

	bool bShouldRemove = false;

	for (TFieldIterator<FProperty> It(Function); It; ++It)
	{
		if (!It->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			Builder.Append(FString::Printf(TEXT(
				"\"%s\", "
			),
			                               *It->GetName()
			));

			bShouldRemove = true;
		}
	}

	if (bShouldRemove)
	{
		Builder.RemoveSuffix(2);
	}

	Builder.Append(TEXT("}"));

	return Builder.ToString();
}

FString FSourceCodeGeneratorModule::GetFunctionDefaultValue(const UFunction* Function)
{
	if (!Function->HasAnyFunctionFlags(FUNC_BlueprintCallable))
	{
		return FString();
	}

	FSmallStringBuilder Builder;

	const TMap<FName, FString>* MetaMap = UMetaData::GetMapForObject(Function);

	for (TFieldIterator<FProperty> It(Function); It; ++It)
	{
		if (It->HasAnyPropertyFlags(CPF_Parm) && !It->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			FString ValueStr;

			if (FindDefaultValueString(MetaMap, *It, ValueStr))
			{
				Builder.Append(", ");

				if (ValueStr == "NULL")
				{
					Builder.Append("nullptr");
				}
				else
				{
					Builder.Append(ValueStr);
				}
			}
		}
	}

	return Builder.ToString();
}

void FSourceCodeGeneratorModule::GetPropertySignature(const FProperty* Property, FString& OutString)
{
	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		OutString.Append(FString::Printf(TEXT(
			"TArray<%s>"
		),
		                                 *ArrayProperty->Inner->GetCPPType()
		));
	}
	else if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		OutString.Append(FString::Printf(TEXT(
			"TSet<%s>"
		),
		                                 *SetProperty->ElementProp->GetCPPType()
		));
	}
	else if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		OutString.Append(FString::Printf(TEXT(
			"TMap<%s, %s>"
		),
		                                 *MapProperty->KeyProp->GetCPPType(),
		                                 *MapProperty->ValueProp->GetCPPType()
		));
	}
	else if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		OutString.Append(FString::Printf(TEXT(
			"TScriptInterface<I%s>"
		),
		                                 *InterfaceProperty->InterfaceClass->GetName()
		));
	}
	else
	{
		OutString.Append(Property->GetCPPType());
	}
}

void FSourceCodeGeneratorModule::GetDependencyClasses(const FProperty* Property, TSet<UClass*>& DependencyClasses)
{
	if (const auto ClassProperty = CastField<FClassProperty>(Property))
	{
		if (ClassProperty->MetaClass != nullptr)
		{
			DependencyClasses.Add(ClassProperty->MetaClass);
		}
	}
	else if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		if (ObjectProperty->PropertyClass != nullptr)
		{
			DependencyClasses.Add(ObjectProperty->PropertyClass);
		}
	}
	else if (const auto ObjectPtrProperty = CastField<FObjectPtrProperty>(Property))
	{
		if (ObjectPtrProperty->PropertyClass != nullptr)
		{
			DependencyClasses.Add(ObjectPtrProperty->PropertyClass);
		}
	}
	else if (const auto SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		if (SoftClassProperty->MetaClass != nullptr)
		{
			DependencyClasses.Add(SoftClassProperty->MetaClass);
		}
	}
	else if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		if (SoftObjectProperty->PropertyClass != nullptr)
		{
			DependencyClasses.Add(SoftObjectProperty->PropertyClass);
		}
	}
	else if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		if (ArrayProperty->Inner != nullptr)
		{
			GetDependencyClasses(ArrayProperty->Inner, DependencyClasses);
		}
	}
}

void FSourceCodeGeneratorModule::SaveIfChanged(const FString& FileName, const FString& String)
{
	if (FPaths::FileExists(FileName))
	{
		FString FileContent;

		if (FFileHelper::LoadFileToString(FileContent, *FileName) && FileContent == String)
		{
			return;
		}

		FFileHelper::SaveStringToFile(builder, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	}
}

FString FSourceCodeGeneratorModule::GetHeaderFile(UClass* InClass)
{
	return FPaths::Combine(HeaderPath.FindRef(FPaths::GetCleanFilename(InClass->GetPackage()->GetName())),
	                       InClass->GetMetaData("ModuleRelativePath"));
}

FString FSourceCodeGeneratorModule::GenerateInclude(const FString& FileName)
{
	return FString::Printf(TEXT(
		"#include \"%s\"\n"
	),
	                       *FileName
	);
}

FString FSourceCodeGeneratorModule::GetInclude(UClass* InClass)
{
	return GenerateInclude(GetHeaderFile(InClass));
}

void FSourceCodeGeneratorModule::GetPlugins(const FString& InPathName, TMap<FString, FString>& Plugins)
{
	const FString Suffix = FString(TEXT("*.uplugin"));

	IFileManager& MyFileManager = IFileManager::Get();

	if (MyFileManager.DirectoryExists(*InPathName))
	{
		TArray<FString> FileNames;

		MyFileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);

		for (auto& PluginName : FileNames)
		{
			Plugins.Add(
				FPaths::GetCleanFilename(PluginName).Left(
					FPaths::GetCleanFilename(PluginName).Len() - Suffix.Len() + 1),
				FPaths::ConvertRelativePathToFull(FPaths::GetPath(PluginName)));
		}
	}
}

void FSourceCodeGeneratorModule::GetModules(const FString& InPathName, TMap<FString, FString>& Modules)
{
	const FString Suffix = FString(TEXT("*.Build.cs"));

	IFileManager& MyFileManager = IFileManager::Get();

	if (MyFileManager.DirectoryExists(*InPathName))
	{
		TArray<FString> FileNames;

		MyFileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);

		for (auto& PluginName : FileNames)
		{
			Modules.Add(
				FPaths::GetCleanFilename(PluginName).Left(
					FPaths::GetCleanFilename(PluginName).Len() - Suffix.Len() + 1),
				FPaths::ConvertRelativePathToFull(FPaths::GetPath(PluginName)));
		}
	}
}

void FSourceCodeGeneratorModule::GetModules(const FString& InPathName, TSet<FString>& Modules)
{
	const FString Suffix = FString(TEXT("*.Build.cs"));

	IFileManager& MyFileManager = IFileManager::Get();

	if (MyFileManager.DirectoryExists(*InPathName))
	{
		TArray<FString> FileNames;

		MyFileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);

		for (auto& PluginName : FileNames)
		{
			Modules.Add(
				FPaths::GetCleanFilename(PluginName).Left(
					FPaths::GetCleanFilename(PluginName).Len() - Suffix.Len() + 1));
		}
	}
}

bool FSourceCodeGeneratorModule::FindDefaultValueString(const TMap<FName, FString>* MetaMap, const FProperty* Param, FString& OutString)
{
	if (MetaMap == nullptr || Param == nullptr)
	{
		return false;
	}

	const FName ParamName(*Param->GetName());

	const FName CppKey(*(FString(TEXT("CPP_Default_")) + ParamName.ToString()));

	if (!MetaMap->Contains(CppKey))
	{
		return false;
	}

	if (Param->IsA<FObjectProperty>()
		|| Param->IsA<FObjectPtrProperty>()
		|| Param->IsA<FClassPtrProperty>())
	{
		OutString = TEXT("nullptr");
	}
	else
	{
		FString InMetaData;

		if (const FString* CppDefaultValue = MetaMap->Find(CppKey))
		{
			if (!CppDefaultValue->IsEmpty())
			{
				InMetaData = *CppDefaultValue;
			}
		}

		if (const auto StructProperty = CastField<FStructProperty>(Param))
		{
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{
				TArray<FString> Value;

				InMetaData.ParseIntoArray(Value, TEXT(","));

				if (Value.Num() == 3)
				{
					OutString = FString::Printf(TEXT(
						"FVector(%lf, %lf, %lf)"
					),
					                            TCString<TCHAR>::Atod(*Value[0]),
					                            TCString<TCHAR>::Atod(*Value[1]),
					                            TCString<TCHAR>::Atod(*Value[2])
					);
				}
			}
			else if (StructProperty->Struct == TBaseStructure<FVector2D>::Get())
			{
				FVector2D Value;

				if (Value.InitFromString(InMetaData))
				{
					OutString = FString::Printf(TEXT(
						"FVector2D(%lf, %lf)"
					),
					                            Value.X,
					                            Value.Y
					);
				}
			}
			else if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
			{
				TArray<FString> Value;

				InMetaData.ParseIntoArray(Value, TEXT(","));

				if (Value.Num() == 3)
				{
					OutString = FString::Printf(TEXT(
						"FRotator(%lf, %lf, %lf)"
					),
					                            TCString<TCHAR>::Atod(*Value[0]),
					                            TCString<TCHAR>::Atod(*Value[1]),
					                            TCString<TCHAR>::Atod(*Value[2])
					);
				}
			}
			else if (StructProperty->Struct == TBaseStructure<FLinearColor>::Get())
			{
				FLinearColor Value;

				if (Value.InitFromString(InMetaData))
				{
					OutString = FString::Printf(TEXT(
						"FLinearColor(%ff, %ff, %ff, %ff)"
					),
					                            Value.R,
					                            Value.G,
					                            Value.B,
					                            Value.A
					);
				}
			}

			if (OutString.IsEmpty())
			{
				OutString = FString::Printf(TEXT(
					"%s%s()"
				),
				                            StructProperty->Struct->GetPrefixCPP(),
				                            *StructProperty->Struct->GetName()
				);
			}
		}
		else if (Param->IsA<FStrProperty>())
		{
			OutString = FString::Printf(TEXT("FString(\"%s\")"), *InMetaData);
		}
		else if (Param->IsA<FNameProperty>())
		{
			OutString = FString::Printf(TEXT("TEXT(\"%s\")"), *InMetaData);
		}
		else if (Param->IsA<FTextProperty>())
		{
			static auto InvText = FString(TEXT("INVTEXT"));

			if (InMetaData.Contains(InvText))
			{
				InMetaData = InMetaData.Mid(InvText.Len() + 2, InMetaData.Len() - InvText.Len() - 4);
			}

			OutString = FString::Printf(TEXT(
				"INVTEXT(\"%s\")"
			),
			                            *InMetaData
			);
		}
		else if (!InMetaData.IsEmpty())
		{
			OutString = InMetaData;
		}
	}

	return !OutString.IsEmpty();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSourceCodeGeneratorModule, SourceCodeGenerator)
