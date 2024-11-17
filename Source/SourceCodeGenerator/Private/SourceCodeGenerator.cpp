#include "SourceCodeGenerator.h"
#include "Features/IModularFeatures.h"
#include "Misc/FileHelper.h"
#include "UObject/CoreNet.h"
#include "UObject/Interface.h"

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
	OutputPath = OutputDirectory;

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

void FSourceCodeGeneratorModule::ExportClass(UClass* Class, const FString& SourceHeaderFilename,
                                             const FString& GeneratedHeaderFilename, bool bHasChanged)
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
			"namespace\r\n"
			"{\r\n"
			"\tstruct FRegister%s\r\n"
			"\t{\r\n"
			"\t\tFRegister%s()\r\n"
			"\t\t{\r\n"
			"\t\t\tTBindingClassBuilder<%s>(NAMESPACE_BINDING)\r\n"
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

		StringBuilder.Append(TEXT("\r\n"));

		BodyBuilder.RemoveSuffix(2);

		BodyBuilder.Appendf(TEXT(
			";\r\n"
			"\t\t}\r\n"
			"\t};\r\n"
			"\r\n"
			"\t[[maybe_unused]] FRegister%s Register%s;\r\n"
			"}\r\n\r\n"
		),
		                    *Class->GetName(),
		                    *Class->GetName()
		);

		StringBuilder.Append(BodyBuilder);

		StringBuilder.Append(TEXT("PRAGMA_ENABLE_DEPRECATION_WARNINGS\r\n"));

		const auto FilePath = FPaths::Combine(OutputPath, *Class->GetName() + BindingSuffix);

		SaveIfChanged(FilePath, StringBuilder.ToString());

		ExportClasses.AddUnique(Class);
	}
}

void FSourceCodeGeneratorModule::FinishExport()
{
	TMap<UPackage*, TArray<FString>> Packages;

	for (const auto ExportClass : ExportClasses)
	{
		Packages.FindOrAdd(ExportClass->GetPackage()).Add(*ExportClass->GetName());
	}

	for (auto& [Key, Value] : Packages)
	{
		Value.Sort();

		FBigStringBuilder StringBuilder;

		StringBuilder.Append(TEXT("#pragma once\r\n\r\n"));

		for (const auto& Name : Value)
		{
			StringBuilder.Append(GenerateInclude(*Name + BindingSuffix));
		}

		const auto FilePath = FPaths::Combine(
			OutputPath, *FPaths::GetCleanFilename(Key->GetName()) + HeaderSuffix);

		SaveIfChanged(FilePath, StringBuilder.ToString());
	}
}

FString FSourceCodeGeneratorModule::GetGeneratorName() const
{
	return TEXT("UnrealCSharp Source Code Generator");
}

bool FSourceCodeGeneratorModule::CanExportClass(const UClass* Class)
{
	return !Class->HasAnyClassFlags(CLASS_Interface) &&
		IsClassTypeSupported(Class);
}

bool FSourceCodeGeneratorModule::CanExportFunction(const UFunction* Function)
{
	if (const auto OwnerClass = Function->GetOwnerClass())
	{
		if (!OwnerClass->HasAnyClassFlags(CLASS_RequiredAPI) &&
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

	if (Function->HasMetaData(FName(TEXT("CustomThunk"))))
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

	for (TFieldIterator<FProperty> Property(Function); Property; ++Property)
	{
		if (!IsPropertyTypeSupported(*Property))
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

void FSourceCodeGeneratorModule::ExportFunction(FBigStringBuilder& StringBuilder,
                                                const UClass* Class,
                                                const UFunction* Function)
{
	StringBuilder.Appendf(TEXT(
		"\t\t\t\t.Function(\"%s\", BINDING_OVERLOAD(%s, &%s::%s"
	),
	                      *Function->GetName(),
	                      *GetFunctionSignature(Class, Function),
	                      *(Class->GetPrefixCPP() + Class->GetName()),
	                      *Function->GetName());

	auto bHasParameters = false;

	for (TFieldIterator<FProperty> Property(Function); Property; ++Property)
	{
		if (Property->HasAnyPropertyFlags(CPF_Parm) && !Property->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			bHasParameters = true;

			break;
		}
	}

	if (bHasParameters)
	{
		StringBuilder.Appendf(TEXT(
			", %s"
		),
		                      *GetFunctionParamName(Function));
	}

	if (!Function->HasAnyFunctionFlags(FUNC_Static))
	{
		StringBuilder.Append(TEXT(", EFunctionInteract::Virtual"));
	}

	if (bHasParameters)
	{
		StringBuilder.Append(GetFunctionDefaultValue(Function));
	}

	StringBuilder.Append(TEXT("))\r\n"));
}

void FSourceCodeGeneratorModule::ExportProperty(FBigStringBuilder& StringBuilder,
                                                const UClass* Class,
                                                const FProperty* Property)
{
	StringBuilder.Appendf(TEXT(
		"\t\t\t\t.Property(\"%s\", BINDING_PROPERTY(&%s::%s))\r\n"
	),
	                      *Property->GetNameCPP(),
	                      *(Class->GetPrefixCPP() + Class->GetName()),
	                      *Property->GetNameCPP());
}

bool FSourceCodeGeneratorModule::IsClassTypeSupported(const UClass* Class)
{
	return !Class->HasAnyClassFlags(CLASS_Deprecated) &&
	(Class == UObject::StaticClass() ||
		Class == UClass::StaticClass() ||
		Class->HasAnyClassFlags(CLASS_RequiredAPI | CLASS_MinimalAPI));
}

bool FSourceCodeGeneratorModule::IsPropertyTypeSupported(const FProperty* Property)
{
	if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		if (!IsClassTypeSupported(ObjectProperty->PropertyClass))
		{
			return false;
		}
	}

	if (const auto ObjectPtrProperty = CastField<FObjectPtrProperty>(Property))
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

	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		return IsPropertyTypeSupported(ArrayProperty->Inner);
	}

	if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		return IsPropertyTypeSupported(SetProperty->ElementProp);
	}

	if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		return IsPropertyTypeSupported(MapProperty->KeyProp) &&
			IsPropertyTypeSupported(MapProperty->ValueProp);
	}

	auto bIsBitField = false;

	if (const auto BoolProperty = CastField<FBoolProperty>(Property))
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

	FString String;

	auto bIsConst = false;

	if (Property->HasAnyPropertyFlags(CPF_ConstParm) || Property->HasMetaData(FName(TEXT("NativeConst"))))
	{
		String.Append(TEXT("const "));

		bIsConst = true;
	}

	GetPropertySignature(Property, String);

	if (Property->IsA<FStrProperty>())
	{
		if (bIsConst &&
			!Property->HasAnyPropertyFlags(CPF_ConstParm))
		{
			String.Append(TEXT("&"));
		}
	}
	else if (Property->HasAnyPropertyFlags(CPF_ReferenceParm) &&
		Property->HasAnyPropertyFlags(CPF_ConstParm))
	{
		String.Append(TEXT("&"));
	}

	return String;
}

FString FSourceCodeGeneratorModule::GetParamPropertySignature(const FProperty* Property)
{
	if (Property == nullptr)
	{
		return TEXT("void");
	}

	FString String;

	auto bIsConst = false;

	if (Property->HasAnyPropertyFlags(CPF_ConstParm) || Property->HasMetaData(FName(TEXT("NativeConst"))))
	{
		String.Append(TEXT("const "));

		bIsConst = true;
	}

	GetPropertySignature(Property, String);

	if (Property->IsA<FStrProperty>())
	{
		if (bIsConst &&
			!Property->HasAnyPropertyFlags(CPF_ConstParm) ||
			Property->HasAnyPropertyFlags(CPF_OutParm))
		{
			String.Append(TEXT("&"));
		}
	}
	else if (Property->HasAnyPropertyFlags(CPF_OutParm) ||
		Property->HasAnyPropertyFlags(CPF_ReferenceParm))
	{
		String.Append(TEXT("&"));
	}

	return String;
}

FString FSourceCodeGeneratorModule::GetFunctionSignature(const UClass* Class, const UFunction* Function)
{
	FString String;

	String.Append(GetReturnPropertySignature(Function->GetReturnProperty()));

	if (Function->HasAnyFunctionFlags(FUNC_Static))
	{
		String.Append(TEXT("(*)"));
	}
	else
	{
		String.Appendf(TEXT(
			"(%s::*)"
		),
		               *(Class->GetPrefixCPP() + Class->GetName())
		);
	}

	String.Append(TEXT("("));

	auto bHasParameters = false;

	for (TFieldIterator<FProperty> Property(Function); Property; ++Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			String.Append(GetParamPropertySignature(*Property));

			String.Append(TEXT(", "));

			bHasParameters = true;
		}
	}

	if (bHasParameters)
	{
		String.LeftInline(String.Len() - 2);
	}

	String.Append(TEXT(")"));

	if (Function->HasAnyFunctionFlags(FUNC_Const))
	{
		String.Append(TEXT("const"));
	}

	return String;
}

FString FSourceCodeGeneratorModule::GetFunctionParamName(const UFunction* Function)
{
	FSmallStringBuilder Builder;

	Builder.Append(TEXT("TArray<FString>{"));

	auto bIsConst = false;

	for (TFieldIterator<FProperty> Property(Function); Property; ++Property)
	{
		if (!Property->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			Builder.Appendf(TEXT(
				"\"%s\", "
			),
			                *Property->GetName()
			);

			bIsConst = true;
		}
	}

	if (bIsConst)
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

	const auto MetaDataMap = UMetaData::GetMapForObject(Function);

	for (TFieldIterator<FProperty> Property(Function); Property; ++Property)
	{
		if (Property->HasAnyPropertyFlags(CPF_Parm) && !Property->HasAnyPropertyFlags(CPF_ReturnParm))
		{
			if (FString Value; FindDefaultValue(MetaDataMap, *Property, Value))
			{
				Builder.Append(TEXT(", "));

				if (Value == TEXT("NULL"))
				{
					Builder.Append(TEXT("nullptr"));
				}
				else
				{
					Builder.Append(Value);
				}
			}
		}
	}

	return Builder.ToString();
}

bool FSourceCodeGeneratorModule::FindDefaultValue(const TMap<FName, FString>* MetaDataMap, const FProperty* Param,
                                                  FString& OutString)
{
	if (MetaDataMap == nullptr || Param == nullptr)
	{
		return false;
	}

	const FName ParamName(*Param->GetName());

	const FName CppKey(*(FString(TEXT("CPP_Default_")) + ParamName.ToString()));

	if (!MetaDataMap->Contains(CppKey))
	{
		return false;
	}

	if (Param->IsA<FObjectProperty>()
		|| Param->IsA<FClassPtrProperty>()
		|| Param->IsA<FObjectPtrProperty>())
	{
		OutString = TEXT("nullptr");
	}
	else
	{
		FString MetaData;

		if (const auto CppDefaultValue = MetaDataMap->Find(CppKey))
		{
			if (!CppDefaultValue->IsEmpty())
			{
				MetaData = *CppDefaultValue;
			}
		}

		if (const auto StructProperty = CastField<FStructProperty>(Param))
		{
			if (StructProperty->Struct == TBaseStructure<FVector>::Get())
			{
				TArray<FString> Value;

				MetaData.ParseIntoArray(Value, TEXT(","));

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
				if (FVector2D Value; Value.InitFromString(MetaData))
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

				MetaData.ParseIntoArray(Value, TEXT(","));

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
				if (FLinearColor Value; Value.InitFromString(MetaData))
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
			OutString = FString::Printf(TEXT(
				"FString(\"%s\")"
			),
			                            *MetaData);
		}
		else if (Param->IsA<FNameProperty>())
		{
			OutString = FString::Printf(TEXT(
				"TEXT(\"%s\")"
			),
			                            *MetaData);
		}
		else if (Param->IsA<FTextProperty>())
		{
			static auto InvText = FString(TEXT("INVTEXT"));

			if (MetaData.Contains(InvText))
			{
				MetaData.MidInline(InvText.Len() + 2, MetaData.Len() - InvText.Len() - 4);
			}

			OutString = FString::Printf(TEXT(
				"INVTEXT(\"%s\")"
			),
			                            *MetaData
			);
		}
		else
		{
			OutString = MetaData;
		}
	}

	return !OutString.IsEmpty();
}

void FSourceCodeGeneratorModule::GetPropertySignature(const FProperty* Property, FString& String)
{
	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		String.Appendf(TEXT(
			"TArray<%s>"
		),
		               *ArrayProperty->Inner->GetCPPType()
		);
	}
	else if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		String.Appendf(TEXT(
			"TSet<%s>"
		),
		               *SetProperty->ElementProp->GetCPPType()
		);
	}
	else if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		String.Appendf(TEXT(
			"TMap<%s, %s>"
		),
		               *MapProperty->KeyProp->GetCPPType(),
		               *MapProperty->ValueProp->GetCPPType()
		);
	}
	else if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		String.Appendf(TEXT(
			"TScriptInterface<I%s>"
		),
		               *InterfaceProperty->InterfaceClass->GetName()
		);
	}
	else
	{
		String.Append(Property->GetCPPType());
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
	else if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		if (SetProperty->ElementProp != nullptr)
		{
			GetDependencyClasses(SetProperty->ElementProp, DependencyClasses);
		}
	}
	else if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		if (MapProperty->KeyProp != nullptr && MapProperty->ValueProp != nullptr)
		{
			GetDependencyClasses(MapProperty->KeyProp, DependencyClasses);

			GetDependencyClasses(MapProperty->ValueProp, DependencyClasses);
		}
	}
}

void FSourceCodeGeneratorModule::SaveIfChanged(const FString& FileName, const FString& String)
{
	if (FPaths::FileExists(FileName))
	{
		if (FString Result; FFileHelper::LoadFileToString(Result, *FileName) && Result == String)
		{
			return;
		}
	}

	FFileHelper::SaveStringToFile(String, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
}

FString FSourceCodeGeneratorModule::GetHeaderFile(UClass* Class)
{
	FString ModuleRelativePath = Class->GetMetaData(TEXT("ModuleRelativePath"));

	if (ModuleRelativePath.IsEmpty())
	{
		if (Class == UInterface::StaticClass())
		{
			ModuleRelativePath = TEXT("Public/UObject/Interface.h");
		}
		else if (Class == UPackageMap::StaticClass())
		{
			ModuleRelativePath = TEXT("Public/UObject/CoreNet.h");
		}
	}

	return FPaths::Combine(HeaderPath.FindRef(FPaths::GetCleanFilename(Class->GetPackage()->GetName())),
	                       ModuleRelativePath);
}

FString FSourceCodeGeneratorModule::GenerateInclude(const FString& FileName)
{
	return FString::Printf(TEXT(
		"#include \"%s\"\n"
	),
	                       *FileName
	);
}

FString FSourceCodeGeneratorModule::GetInclude(UClass* Class)
{
	return GenerateInclude(GetHeaderFile(Class));
}

void FSourceCodeGeneratorModule::GetPlugins(const FString& InPathName, TMap<FString, FString>& Plugins)
{
	const auto Suffix = FString(TEXT("*.uplugin"));

	if (auto& FileManager = IFileManager::Get(); FileManager.DirectoryExists(*InPathName))
	{
		TArray<FString> FileNames;

		FileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);

		for (const auto& FileName : FileNames)
		{
			Plugins.Add(
				FPaths::GetCleanFilename(FileName).Left(
					FPaths::GetCleanFilename(FileName).Len() - Suffix.Len() + 1),
				FPaths::ConvertRelativePathToFull(FPaths::GetPath(FileName)));
		}
	}
}

void FSourceCodeGeneratorModule::GetModules(const FString& InPathName, TMap<FString, FString>& Modules)
{
	const auto Suffix = FString(TEXT("*.Build.cs"));

	if (auto& FileManager = IFileManager::Get(); FileManager.DirectoryExists(*InPathName))
	{
		TArray<FString> FileNames;

		FileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);

		for (const auto& FileName : FileNames)
		{
			Modules.Add(
				FPaths::GetCleanFilename(FileName).Left(
					FPaths::GetCleanFilename(FileName).Len() - Suffix.Len() + 1),
				FPaths::ConvertRelativePathToFull(FPaths::GetPath(FileName)));
		}
	}
}

void FSourceCodeGeneratorModule::GetModules(const FString& InPathName, TSet<FString>& Modules)
{
	const auto Suffix = FString(TEXT("*.Build.cs"));

	if (auto& FileManager = IFileManager::Get(); FileManager.DirectoryExists(*InPathName))
	{
		TArray<FString> FileNames;

		FileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);

		for (const auto& FileName : FileNames)
		{
			Modules.Add(
				FPaths::GetCleanFilename(FileName).Left(
					FPaths::GetCleanFilename(FileName).Len() - Suffix.Len() + 1));
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSourceCodeGeneratorModule, SourceCodeGenerator)
