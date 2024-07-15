#include <iostream>

#include "CoreUObject.h"
#include "Features/IModularFeatures.h"
#include "Modules/ModuleManager.h"
#include "Programs/UnrealHeaderTool/Public/IScriptGeneratorPluginInterface.h"
#include "IScriptGeneratorPluginInterface.h"

#define LOCTEXT_NAMESPACE "FSourceCodeGeneratorModule"

#define STRING_BUILDER_BUFFER_SIZE 256 * 1024

static bool FindDefaultValueString(const TMap<FName, FString>* MetaMap, const FProperty* Param, FString& OutString)
{
	if (MetaMap == nullptr || Param == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("\t\t\t\t\t UnrealCSharpGenCodeError : FindDefaultValueString : MetaMap == nullptr || Param == nullptr\n"));
		
		return false;
	}

	const FName ParamName(*Param->GetName());

	const FName CppKey(*(FString(TEXT("CPP_Default_")) + ParamName.ToString()));

	if (!MetaMap->Contains(CppKey))
	{
		return false;
	}

	if (Param->IsA(FObjectProperty::StaticClass())
		|| Param->IsA(FObjectPtrProperty::StaticClass())
		|| Param->IsA(FClassPtrProperty::StaticClass())
	)
	{
		OutString = TEXT("nullptr");
		return true;
	}

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
		if (StructProperty->Struct == TBaseStructure<FRotator>::Get())
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

				return true;
			}
		}

		if (StructProperty->Struct == TBaseStructure<FLinearColor>::Get())
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

				return true;
			}
		}

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

				return true;
			}
		}

		if (StructProperty->Struct == TBaseStructure<FVector2D>::Get())
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

				return true;
			}
		}

		OutString = FString::Printf(TEXT(
			"%s%s()"
		),
		                            StructProperty->Struct->GetPrefixCPP(),
		                            *StructProperty->Struct->GetName()
		);

		return true;
	}

	if (Param->IsA(FStrProperty::StaticClass())) // FString
	{
		OutString = FString::Printf(TEXT("FString(\"%s\")"), *InMetaData);
		return true;
	}

	if (Param->IsA(FNameProperty::StaticClass()))
	{
		OutString = FString::Printf(TEXT("TEXT(\"%s\")"), *InMetaData);
		return true;
	}

	if (Param->IsA(FTextProperty::StaticClass()))
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
		return true;
	}

	if (OutString.IsEmpty() && !InMetaData.IsEmpty())
	{
		OutString = InMetaData;
	}

	return true;
}

class FSourceCodeGeneratorModule : public IScriptGeneratorPluginInterface
{
public:
	virtual void StartupModule() override
	{
		IModularFeatures::Get().RegisterModularFeature(TEXT("ScriptGenerator"), this);
	}

	virtual void ShutdownModule() override
	{
		IModularFeatures::Get().UnregisterModularFeature(TEXT("ScriptGenerator"), this);
	}

	virtual FString GetGeneratedCodeModuleName() const override
	{
		return TEXT("UnrealCSharp");
	}

	virtual bool SupportsTarget(const FString& TargetName) const override
	{
		FString SettingFile = FPaths::Combine(
			FPaths::ConvertRelativePathToFull(FPaths::GetPath(FPaths::GetProjectFilePath())),
			TEXT("Config/DefaultUnrealCSharpEditorSetting.ini"));

		bool bSupport = false;

		if (FPaths::FileExists(SettingFile))
		{
			GConfig->GetBool(
				TEXT("/Script/UnrealCSharpCore.UnrealCSharpEditorSetting"), TEXT("bEnableExport"), bSupport,
				SettingFile);
		}

		return bSupport;
	}

	virtual bool ShouldExportClassesForModule(const FString& ModuleName, EBuildModuleType::Type ModuleType,
	                                          const FString& ModuleGeneratedIncludeDirectory) const override
	{
		return ExportModules.Contains(ModuleName) &&
			(ModuleType == EBuildModuleType::EngineRuntime || ModuleType == EBuildModuleType::GameRuntime);
	}

	virtual void Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory,
	                        const FString& IncludeBase) override
	{
		Project.Empty();

		HeaderPath.Empty();

		OutputDir = FPaths::Combine(OutputDirectory, TEXT("UHT/"));

		ProjectPath = FPaths::ConvertRelativePathToFull(FPaths::GetPath(FPaths::GetProjectFilePath()));

		ProjectSourcePath = FPaths::Combine(ProjectPath, TEXT("Source/"));

		ProjectPluginsPath = FPaths::Combine(ProjectPath, TEXT("Plugins/"));

		EngineSourcePath = FPaths::EngineSourceDir();

		EnginePluginsPath = FPaths::EnginePluginsDir();

		ConfigFilePath = FPaths::Combine(ProjectPath, TEXT("Config/DefaultUnrealCSharpEditorSetting.ini"));

		ConfigSection = TEXT("/Script/UnrealCSharpCore.UnrealCSharpEditorSetting");

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
		else
		{
			UE_LOG(LogTemp, Error, TEXT("\t\t\t\t\t UnrealCSharpGenCodeError : Config file not found\n"));
		}
	}

	static void ExportProperty(TStringBuilder<STRING_BUILDER_BUFFER_SIZE>& StringBuilder, const UClass* Class,
	                           const FProperty* Property)
	{
		StringBuilder.Append(FString::Printf(
			TEXT("\t\t\t.Property(\"%s\", BINDING_PROPERTY(&%s::%s))\r\n"), *Property->GetNameCPP(),
			*(Class->GetPrefixCPP() + Class->GetName()), *Property->GetNameCPP()));
	}

	static void ExportFunction(TStringBuilder<STRING_BUILDER_BUFFER_SIZE>& StringBuilder, const UClass* Class,
	                           const UFunction* Function)
	{
		StringBuilder.Append(
			FString::Printf(
				TEXT("\t\t\t.Function(\"%s\", BINDING_OVERLOAD(%s, &%s::%s"), *Function->GetName(),
				*GetFunctionSignature(Class, Function), *(Class->GetPrefixCPP() + Class->GetName()),
				*Function->GetName()));

		bool bHasPam = false;

		for (TFieldIterator<FProperty> It(Function); It; ++It)
		{
			if (It->HasAnyPropertyFlags(CPF_Parm) && !It->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				bHasPam = true;
				break;
			}
		}

		if (bHasPam)
		{
			StringBuilder.Append(FString::Printf(TEXT(", %s"), *GetFunctionParamName(Function)));
		}

		if (!Function->HasAnyFunctionFlags(FUNC_Static))
		{
			StringBuilder.Append(TEXT(", EFunctionInteract::Virtual"));
		}

		if (bHasPam)
		{
			StringBuilder.Append(GetFunctionDefaultValue(Function));
		}

		StringBuilder.Append("))\r\n");
	}

	virtual void ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename,
	                         bool bHasChanged) override
	{
		if (CanExportClass(Class))
		{
			TSet<UClass*> DependencyClasses = TSet({Class});

			TStringBuilder<STRING_BUILDER_BUFFER_SIZE> StringBuilder;

			TStringBuilder<STRING_BUILDER_BUFFER_SIZE> BodyBuilder;

			StringBuilder.Append(
				"#pragma once\r\n\r\n"
				"PRAGMA_DISABLE_DEPRECATION_WARNINGS\r\n\r\n");

			BodyBuilder.Append(FString::Printf(TEXT(
				"struct FRegister%s\r\n"
				"{\r\n"
				"\tFRegister%s()\r\n"
				"\t{\r\n"
				"\t\tTBindingClassBuilder<%s>(NAMESPACE_BINDING)\r\n"
			),
			                                   *Class->GetName(),
			                                   *Class->GetName(),
			                                   *(Class->GetPrefixCPP() + Class->GetName())
			));

			for (TFieldIterator<FProperty> PropIt(Class, EFieldIterationFlags::None); PropIt; ++PropIt)
			{
				if (CanExportProperty(*PropIt))
				{
					GetDependencyClasses(*PropIt, DependencyClasses);

					ExportProperty(BodyBuilder, Class, *PropIt);
				}
			}

			for (TFieldIterator<UFunction> FuncIt(Class, EFieldIterationFlags::None); FuncIt; ++FuncIt)
			{
				if (CanExportFunction(*FuncIt))
				{
					for (TFieldIterator<FProperty> It(*FuncIt); It; ++It)
					{
						GetDependencyClasses(*It, DependencyClasses);
					}

					ExportFunction(BodyBuilder, Class, *FuncIt);
				}
			}

			for (const auto DependencyClass : DependencyClasses)
			{
				StringBuilder.Append(GetInclude(DependencyClass));
			}

			StringBuilder.Append("\r\n");

			BodyBuilder.RemoveSuffix(2);

			BodyBuilder.Append(FString::Printf(TEXT(
				";\r\n"
				"\t}\r\n"
				"};\r\n"
				"\r\n"
				"static FRegister%s Register%s;\r\n\r\n"
			),
			                                   *Class->GetName(),
			                                   *Class->GetName()
			));

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

	virtual void FinishExport() override
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

	virtual FString GetGeneratorName() const override
	{
		return TEXT("UnrealCSharp Script Generator");
	}

protected:
	virtual bool CanExportClass(const UClass* Class)
	{
		return !Class->HasAnyClassFlags(CLASS_Interface) &&
			IsClassTypeSupported(Class);
	}

	virtual bool CanExportFunction(const UFunction* Function)
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
			if (ReturnProperty->IsA(FMapProperty::StaticClass()))
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

	virtual bool CanExportProperty(const FProperty* Property)
	{
		return !Property->HasAnyPropertyFlags(CPF_EditorOnly) &&
			Property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPublic) &&
			IsPropertyTypeSupported(Property);
	}

private:
	static bool IsClassTypeSupported(const UClass* Class)
	{
		return !Class->HasAnyClassFlags(CLASS_Deprecated) &&
		(Class == UObject::StaticClass() ||
			Class->HasAnyClassFlags(CLASS_RequiredAPI | CLASS_MinimalAPI));
	}

	static bool IsPropertyTypeSupported(const FProperty* Property)
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

		if (Property->IsA(FEnumProperty::StaticClass()))
		{
			return false;
		}

		if (Property->IsA(FByteProperty::StaticClass()))
		{
			return false;
		}

		if (Property->IsA(FDelegateProperty::StaticClass()))
		{
			return false;
		}

		if (Property->IsA(FMulticastDelegateProperty::StaticClass()))
		{
			return false;
		}

		if (Property->IsA(FFieldPathProperty::StaticClass()))
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

	static FString GetReturnPropertySignature(const FProperty* Property)
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

		GetPropertySignature_Internal(Property, StringBuilder);

		if (Property->IsA(FStrProperty::StaticClass())) // FString
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

	static FString GetParamPropertySignature(const FProperty* Property)
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

		GetPropertySignature_Internal(Property, StringBuilder);

		if (Property->IsA(FStrProperty::StaticClass())) // FString
		{
			if (bShouldConst &&
				!Property->HasAnyPropertyFlags(CPF_ConstParm) ||
				Property->HasAnyPropertyFlags(CPF_OutParm))
			{
				StringBuilder.Append(TEXT("&"));
			}
		}
		else if (Property->HasAnyPropertyFlags(CPF_OutParm) ||
			Property->HasAnyPropertyFlags(CPF_ReferenceParm))
		{
			StringBuilder.Append(TEXT("&"));
		}

		return StringBuilder;
	}

	static FString GetFunctionSignature(const UClass* Class, const UFunction* Function)
	{
		FString SignatureBuilder;

		SignatureBuilder.Append(GetReturnPropertySignature(Function->GetReturnProperty()));

		if (Function->HasAnyFunctionFlags(FUNC_Static))
		{
			SignatureBuilder.Append(TEXT("(*)"));
		}
		else
		{
			SignatureBuilder.Append(FString::Printf(TEXT(
				"(%s::*)"
			),
			                                        *(Class->GetPrefixCPP() + Class->GetName())
			));
		}

		SignatureBuilder.Append("(");

		bool bIsHasParameter = false;

		for (TFieldIterator<FProperty> PropIt(Function); PropIt; ++PropIt)
		{
			if (!PropIt->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				SignatureBuilder.Append(GetParamPropertySignature(*PropIt));

				SignatureBuilder.Append(TEXT(", "));

				bIsHasParameter = true;
			}
		}

		if (bIsHasParameter)
		{
			SignatureBuilder = SignatureBuilder.Left(SignatureBuilder.Len() - 2);
		}

		SignatureBuilder.Append(TEXT(")"));

		if (Function->HasAnyFunctionFlags(FUNC_Const))
		{
			SignatureBuilder.Append(TEXT("const"));
		}

		return SignatureBuilder;
	}

	static FString GetFunctionParamName(const UFunction* Function)
	{
		FString Builder;

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
			Builder = Builder.Left(Builder.Len() - 2);
		}

		Builder.Append(TEXT("}"));

		return Builder;
	}

	static FString GetFunctionDefaultValue(const UFunction* Function)
	{
		if (!Function->HasAnyFunctionFlags(FUNC_BlueprintCallable))
		{
			return FString();
		}

		FString Builder;

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
					// @TODO Enum
					else if (const auto EnumProperty = CastField<FEnumProperty>(*It))
					{
						Builder.Append(FString::Printf(TEXT(
							"%s::%s"
						),
						                               *EnumProperty->GetEnum()->CppType,
						                               *ValueStr
						));
					}
					// @TODO Byte
					else if (const auto ByteProperty = CastField<FByteProperty>(*It))
					{
						Builder.Append(ValueStr);
					}
					else
					{
						Builder.Append(ValueStr);
					}
				}
			}
		}

		return Builder;
	}

	static void GetPropertySignature_Internal(const FProperty* Property, FString& OutString)
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
		// @TODO Support Byte
		else if (const auto ByteProperty = CastField<FByteProperty>(Property))
		{
			OutString.Append(Property->GetCPPType());
		}
		// @TODO Support Enum
		else if (const auto EnumProperty = CastField<FEnumProperty>(Property))
		{
			OutString.Append(EnumProperty->GetEnum()->CppType);
		}
		else
		{
			OutString.Append(Property->GetCPPType());
		}
	}

	static void GetDependencyClasses(const FProperty* Property, TSet<UClass*>& DependencyClasses)
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

	void SaveIfChanged(FString FileName, const FString& builder)
	{
		if (FPaths::FileExists(FileName))
		{
			FString FileContent;

			if (FFileHelper::LoadFileToString(FileContent, *FileName) && FileContent == builder)
			{
				return;
			}

			FFileHelper::SaveStringToFile(builder, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
		}
	}

	FString GetHeaderFile(UClass* InClass)
	{
		return FPaths::Combine(HeaderPath.FindRef(FPaths::GetCleanFilename(InClass->GetPackage()->GetName())),
		                       InClass->GetMetaData("ModuleRelativePath"));
	}

	static FString GenerateInclude(const FString& FileName)
	{
		return FString::Printf(TEXT(
			"#include \"%s\"\n"
		),
									*FileName
		);
	}

	FString GetInclude(UClass* InClass)
	{
		return GenerateInclude(GetHeaderFile(InClass));
	}

	void GetPlugins(const FString& InPathName, TMap<FString, FString>& Plugins)
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

	void GetModules(const FString& InPathName, TMap<FString, FString>& Modules)
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

	void GetModules(const FString& InPathName, TSet<FString>& Modules)
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

public:
	FString OutputDir;

	FString ProjectPath;

	FString ProjectSourcePath;

	FString ProjectPluginsPath;

	FString EngineSourcePath;

	FString EnginePluginsPath;

	FString ConfigFilePath;

	FString ConfigSection;

	TArray<FString> ExportModules;

	TSet<FString> Project;

	TMap<FString, FString> HeaderPath;

	TMap<FString, TArray<FString>> ModuleHeaderPath;

	const FString BindingSuffix = FString(TEXT(".binding.inl"));

	const FString HeaderSuffix = FString(TEXT(".header.inl"));
};

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FSourceCodeGeneratorModule, SourceCodeGenerator)
