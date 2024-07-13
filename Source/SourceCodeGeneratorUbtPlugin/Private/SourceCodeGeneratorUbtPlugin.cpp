
#include <iostream>

#include "CoreUObject.h"
#include "Features/IModularFeatures.h"
#include "Modules/ModuleManager.h"
#include "Programs/UnrealHeaderTool/Public/IScriptGeneratorPluginInterface.h"
#include "IScriptGeneratorPluginInterface.h"
#include "Serialization/CompactBinary.h"

#define LOCTEXT_NAMESPACE "FSourceCodeGeneratorUbtPluginModule"

#define GET_ZERO_DEFAULT_VALUE(TYPE, CORE) \
if (StructProperty->Struct == TBaseStructure<TYPE>::Get())												\
{																										\
	if (const FString* CppDefaultValue = MetaMap->Find(CppKey))											\
	{																									\
		OutString.Append(*CppDefaultValue);																\
		if (CppDefaultValue->IsEmpty())																	\
		{																								\
			OutString.Append(FString(TEXT(#TYPE)) + FString(TEXT("::Zero")) + FString(TEXT(#CORE)));	\
		}																								\
		return true;																					\
	}																									\
}																	

static bool FindDefaultValueString(const TMap<FName, FString>* MetaMap, const FProperty* Param, FString& OutString)
{
	check(MetaMap && Param);
	
	//OutString.Append(FString::Printf(TEXT("%s = "), *Param->GetCPPType()));

	const FName ParamName(*Param->GetName());

	const FName CppKey(*(FString(TEXT("CPP_Default_")) + ParamName.ToString()));
	
	if (!MetaMap->Contains(CppKey))
	{
		return false;
	}

	if (const auto ByteProperty = Cast<FByteProperty>(Param))
	{
		bool bIsSet = false;
			
		if (ByteProperty->GetIntPropertyEnum() != nullptr)
		{
			if (!ByteProperty->GetIntPropertyEnum()->CppType.IsEmpty())
			{
				OutString.Append(ByteProperty->GetIntPropertyEnum()->CppType);
				bIsSet = true;
			}
		}
			
		if (!bIsSet)
		{
			OutString.Append(ByteProperty->GetCPPType());
		}

		OutString.Append(TEXT("::"));
	}

	// Specified default value in the UFUNCTION metadata
	if (const FString* DefaultValue = MetaMap->Find(ParamName))
	{
		OutString.Append(*DefaultValue);
		if (!DefaultValue->IsEmpty())
		{
			return true;
		}
	}

	if (	Param->IsA(FObjectProperty::StaticClass())
		||	Param->IsA(FObjectPtrProperty::StaticClass())
		||	Param->IsA(FClassPtrProperty::StaticClass())
		)
	{
		OutString.Append(TEXT("nullptr"));
		return true;
	}
	
	if (const FStructProperty* StructProperty = Cast<FStructProperty>(Param))
	{
		GET_ZERO_DEFAULT_VALUE(FVector, Vector);
		GET_ZERO_DEFAULT_VALUE(FVector2D, Vector);
		GET_ZERO_DEFAULT_VALUE(FRotator, Rotator);
	}

	// Default value in the function signature
	if (MetaMap->Find(CppKey))
	{
		if (const FString* CppDefaultValue = MetaMap->Find(CppKey))
		{
			OutString.Append(*CppDefaultValue);
			if (!CppDefaultValue->IsEmpty())
			{
				return true;
			}
		}
	}

	return false;
}

static bool GetIsPassCppArgsByRef(const FProperty* Property)
{
	if (Property->IsA(FArrayProperty::StaticClass())
		|| Property->IsA(FDelegateProperty::StaticClass())
		|| Property->IsA(FInterfaceProperty::StaticClass())
		|| Property->IsA(FLazyObjectProperty::StaticClass())
		|| Property->IsA(FMapProperty::StaticClass())
		|| Property->IsA(FMulticastDelegateProperty::StaticClass())
		|| Property->IsA(FObjectPtrProperty::StaticClass())
		|| Property->IsA(FSetProperty::StaticClass())
		|| Property->IsA(FSoftObjectProperty::StaticClass())
		|| Property->IsA(FStrProperty::StaticClass())
		|| Property->IsA(FTextProperty::StaticClass())
		|| Property->IsA(FWeakObjectProperty::StaticClass())
		)
	{
		return true;
	}
	return false;
}

class FSourceCodeGeneratorUbtPluginModule : public IScriptGeneratorPluginInterface
{
public:
	virtual void StartupModule() override
	{
		IModularFeatures::Get().RegisterModularFeature(TEXT("ScriptGenerator"), this);
		HasGameRuntime = false;
	}
	
	virtual void ShutdownModule() override
	{
		IModularFeatures::Get().UnregisterModularFeature(TEXT("ScriptGenerator"), this);
	}

	virtual FString GetGeneratedCodeModuleName() const override { return TEXT("UnrealCSharp"); }

	virtual bool SupportsTarget(const FString& TargetName) const override { return true; }

	virtual bool ShouldExportClassesForModule(const FString& ModuleName, EBuildModuleType::Type ModuleType, const FString& ModuleGeneratedIncludeDirectory) const override
	{
		FSourceCodeGeneratorUbtPluginModule* NonConstPtr = const_cast<FSourceCodeGeneratorUbtPluginModule*>(this);
		NonConstPtr->ParseModule(ModuleName, ModuleType, ModuleGeneratedIncludeDirectory);
		return ExportModules.Find(ModuleName) != INDEX_NONE && (ModuleType == EBuildModuleType::EngineRuntime || ModuleType == EBuildModuleType::GameRuntime); // only 'EngineRuntime' and 'GameRuntime' are valid
	}

	virtual void Initialize(const FString& RootLocalPath, const FString& RootBuildPath, const FString& OutputDirectory, const FString& IncludeBase) override
    {
        Project.Empty();

		HeaderPath.Empty();

		OutputDir = FPaths::Combine(OutputDirectory, TEXT("UHT/"));

		ProjectPath = TEXT("../../../../../UEProject/UnluaGenCodeTest/");

		ProjectSourcePath = FPaths::Combine(ProjectPath, TEXT("Source/"));

		ProjectPluginsPath = FPaths::Combine(ProjectPath, TEXT("Plugins/"));

		EngineSourcePath = FPaths::EngineSourceDir();

		EnginePluginsPath = FPaths::EnginePluginsDir();

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
		
		GConfig->GetArray(TEXT("/Script/UnrealCSharpCore.UnrealCSharpEditorSetting"), TEXT("+ExportModule"), ExportModules, FPaths::Combine(ProjectPath, TEXT("Config/DefaultUnrealCSharpEditorSetting.ini")));
		
		/*FString ModuleContent;

		for (auto it : Project)
		{
			ModuleContent.Append(FString::Printf(TEXT("Project is %s\n"), *it));
		}

		for (auto it = HeaderPath.CreateIterator(); it; ++it)
		{
			ModuleContent.Append(FString::Printf(TEXT("HeaderPath\tKey : %s\t\t\t\t\tValue : %s\n"), *it.Key(), *it.Value()));
		}
		
		/*TArray<FString> OutStrings;
		GConfig->GetArray(TEXT("/Script/UnrealCSharpCore.UnrealCSharpEditorSetting"), TEXT("+ExportModule"), OutStrings, FPaths::Combine(ProjectPath, TEXT("Config/DefaultUnrealCSharpEditorSetting.ini")));

		for (auto it : OutStrings)
		{
			ModuleContent.Append(it + "\n");
		}#1#

		const FString FilePath = FString::Printf(TEXT("%s"), *FPaths::Combine("../../../../../UEProject/UnluaGenCodeTest/", TEXT("MyTestFile.inl")));

		FFileHelper::SaveStringToFile(ModuleContent, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);*/
    }
	
	static void ExportFunction(FString& StringBuilder, const UClass* Class, const UFunction* Function)
	{
		StringBuilder.Append(
			FString::Printf(TEXT("\t\t\t.Function(\"%s\", BINDING_OVERLOAD(%s, &%s::%s"), *Function->GetName(), *GetFunctionSignature(Class, Function), *(Class->GetPrefixCPP() + Class->GetName()), *Function->GetName()));

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

	static void ExportProperty(FString& StringBuilder, const UClass* Class, const FProperty* Property)
	{
		StringBuilder.Append(FString::Printf(TEXT("\t\t\t.Property(\"%s\", BINDING_PROPERTY(&%s::%s))\r\n"), *Property->GetNameCPP(), *(Class->GetPrefixCPP() + Class->GetName()), *Property->GetNameCPP()));
	}

	virtual void ExportClass(UClass* Class, const FString& SourceHeaderFilename, const FString& GeneratedHeaderFilename, bool bHasChanged) override
	{
		if (!CanExportClass(Class))
		{
			return ;
		}

		FString Builder;

		Builder.Append("#pragma once\r\n\r\n");

		auto DependencyClasses = TSet<UClass*>({Class});

		FString BodyBuilder;

		BodyBuilder.Append(
			FString::Printf(TEXT("struct FRegister%s\r\n"), *Class->GetName()) +
			FString::Printf(TEXT("{\r\n")) +
			FString::Printf(TEXT("\tFRegister%s()\r\n"), *Class->GetName()) +
			FString::Printf(TEXT("\t{\r\n")) +
			FString::Printf(TEXT("\t\tTBindingClassBuilder<%s>(NAMESPACE_BINDING)\r\n"), *(Class->GetPrefixCPP() + Class->GetName() ) )
			);

		bool bExportProperty = false;
		
		for (TFieldIterator<FProperty> It(Class); It; ++It)
		{
			if (!CanExportProperty(Class, *It))
			{
				continue;
			}
			
			if (const auto ClassProperty = Cast<FClassProperty>(*It))
			{
				if (ClassProperty->MetaClass != nullptr)
				{
					DependencyClasses.Add(ClassProperty->MetaClass);
				}
			}
			else if (const auto ObjectProperty = Cast<FObjectProperty>(*It))
			{
				DependencyClasses.Add(ObjectProperty->PropertyClass);
			}
			else if (const auto ObjectPtrProperty = Cast<FObjectPtrProperty>(*It))
			{
				DependencyClasses.Add(ObjectPtrProperty->PropertyClass);
			}
			else if (const auto SoftClassProperty = Cast<FSoftClassProperty>(*It))
			{
				if (SoftClassProperty->MetaClass != nullptr)
				{
					DependencyClasses.Add(SoftClassProperty->MetaClass);
				}
			}
			else if (const auto SoftObjectProperty = Cast<FSoftObjectProperty>(*It))
			{
				if (SoftObjectProperty->PropertyClass != nullptr)
				{
					DependencyClasses.Add(SoftObjectProperty->PropertyClass);
				}
			}
			else if (const auto ArrayProperty = Cast<FArrayProperty>(*It))
			{
				if (const auto InnerObjectProperty = Cast<FObjectProperty>(ArrayProperty->Inner))
				{
					DependencyClasses.Add(InnerObjectProperty->PropertyClass);
				}
			}

			ExportProperty(BodyBuilder, Class, *It);

			bExportProperty = true;
		}

		bool bExportFunction = false;
		
		for (TFieldIterator<UFunction> FuncIt(Class); FuncIt; ++FuncIt)
		{
			if (!CanExportFunction(Class, *FuncIt))
			{
				continue;
			}

			for (TFieldIterator<FProperty> It(*FuncIt); It; ++It)
			{
				if (const auto ArrayProperty = Cast<FArrayProperty>(*It))
				{
					if (const auto InnerObjectProperty = Cast<FObjectProperty>(ArrayProperty->Inner))
					{
						DependencyClasses.Add(InnerObjectProperty->PropertyClass);
					}
				}
				else if (const auto ObjectProperty = Cast<FObjectProperty>(*It))
				{
					DependencyClasses.Add(ObjectProperty->PropertyClass);
				}
			}
			
			ExportFunction(BodyBuilder, Class, *FuncIt);
			
			bExportFunction = true;
		}

		for (const auto DependencyClass : DependencyClasses)
		{
			Builder.Append(GetInclude(DependencyClass));
		}

		Builder.Append("\r\n");

		BodyBuilder = BodyBuilder.Left(BodyBuilder.Len() - 2);

		BodyBuilder.Append(
			FString(TEXT(";\r\n")) +
			FString(TEXT("\t}\r\n")) +
			FString(TEXT("};\r\n")) +
			FString(TEXT("\r\n" )) +
			FString::Printf(TEXT("static FRegister%s Register%s;"), *Class->GetName(), *Class->GetName())
		);
		
		ModuleHeaderPath.FindOrAdd(FPaths::GetCleanFilename(Class->GetPackage()->GetName())).Add(*Class->GetName() + BindingSuffix);

		Builder.Append(BodyBuilder);

		const FString FilePath = FString::Printf(TEXT("%s"), *FPaths::Combine(OutputDir, *Class->GetName() + BindingSuffix));

		FFileHelper::SaveStringToFile(Builder, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM); 
	}

	virtual void FinishExport() override
	{
		for (const auto& It : ModuleHeaderPath)
		{
			FString FileContent;
			
			const FString FilePath = FString::Printf(TEXT("%s"), *FPaths::Combine(OutputDir, *It.Key + HeaderSuffix));

			for (const auto& BindingName : It.Value)
			{
				FileContent.Append(FString::Printf(TEXT("#include \"%s\"\n"), *BindingName));
			}

			FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
		}

		// debug
		FString ModuleContent;

		for (auto it : SupportedTypes)
		{
			ModuleContent.Append(FString::Printf(TEXT("SupportedType is %s\n"), *it));
		}

		const FString FilePath = FString::Printf(TEXT("%s"), *FPaths::Combine("../../../../../UEProject/UnluaGenCodeTest/", TEXT("MyTestFile.inl")));
	}

	virtual FString GetGeneratorName() const override
	{
		return TEXT("UnrealCSharp Script Generator");
	}

protected:
	virtual bool CanExportClass(UClass* Class)
	{
		return !Class->HasAnyClassFlags(CLASS_Interface) &&
			   IsClassTypeSupported(Class);
	}

	virtual bool CanExportFunction(UClass* Class, UFunction* function)
	{
		if (function->GetOuterUClass())
		{
			if (function->GetOuterUClass() != Class)
			{
				return false;
			}
		}
		if (function->HasAnyFunctionFlags(FUNC_Delegate | FUNC_MulticastDelegate))
		{
			return false;
		}

		if (!function->HasAnyFunctionFlags(FUNC_Public))
		{
			return false;
		}

		if (function->HasMetaData(FName("CustomThunk")))
		{
			return false;
		}

		if (const auto ReturnProperty = function->GetReturnProperty())
		{
			if (ReturnProperty->IsA(FMapProperty::StaticClass()))
			{
				return false;
			}
		}

		for (TFieldIterator<FProperty> It(function); It ; ++It)
		{
			if (!IsPropertyTypeSupported(*It))
			{
				return false;
			}

			// debug
			if (It)
			{
				AddSupportedType(It->GetCPPType());
			}
		}
		return true;
	}

	virtual bool CanExportProperty(UClass* Class, FProperty* Property)
	{
		if (Property->GetOwnerClass())
		{
			if (Property->GetOwnerClass() != Class)
			{
				return false;
			}
		}
		return Property->HasAnyPropertyFlags(CPF_NativeAccessSpecifierPublic) &&
			   IsPropertyTypeSupported(Property);
	}

private:
	static bool IsClassTypeSupported(UClass* Class)
	{
		return Class->HasAnyClassFlags(CLASS_RequiredAPI | CLASS_MinimalAPI);
	}
	
	static bool IsPropertyTypeSupported(FProperty* property)
	{
		if (const FArrayProperty* ArrayProperty = Cast<FArrayProperty>(property))
		{
			return IsPropertyTypeSupported(ArrayProperty->Inner);
		}

		if (const FObjectProperty* ObjectProperty = Cast<FObjectProperty>(property))
		{
			if (!IsClassTypeSupported(ObjectProperty->PropertyClass))
			{
				return false;
			}
		}

		if (const FObjectPtrProperty* ObjectPtrProperty = Cast<FObjectPtrProperty>(property))
		{
			if (!IsClassTypeSupported(ObjectPtrProperty->PropertyClass))
			{
				return false;
			}
		}
		
		if ( property->IsA(FDelegateProperty::StaticClass()) )
		{
			return false;
		}

		if ( property->IsA(FMulticastDelegateProperty::StaticClass()) )
		{
			return false;
		}

		if (const FStructProperty* FStructPropertyProperty = Cast<FStructProperty>(property))
		{
			if (const auto CppStructOps = FStructPropertyProperty->Struct->GetCppStructOps())
			{
				if (!CppStructOps->HasNoopConstructor())
				{
					return false;
				}
			}
		}

		// Is BitFiled.
		bool bIsBitField = false;
		if (const FBoolProperty* BoolProperty = Cast<FBoolProperty>(property))
		{
			if (!BoolProperty->IsNativeBool())
			{
				bIsBitField = true;
			}
		}

		return !bIsBitField && !(property->ArrayDim > 1);
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

		if (const auto EnumProperty = Cast<FEnumProperty>(Property))
		{
			StringBuilder.Append(EnumProperty->GetEnum()->CppType);
		}
		else if (const auto ArrayProperty = Cast<FArrayProperty>(Property))
		{
			StringBuilder.Append(TEXT("TArray<"));
			StringBuilder.Append(GetParamPropertySignature(ArrayProperty->Inner));
			StringBuilder.Append(TEXT(">"));
		}
		else if (const auto ByteProperty = Cast<FByteProperty>(Property))
		{
			bool bIsSet = false;
			
			if (ByteProperty->GetIntPropertyEnum() != nullptr)
			{
				if (!ByteProperty->GetIntPropertyEnum()->CppType.IsEmpty())
				{
					StringBuilder.Append(ByteProperty->GetIntPropertyEnum()->CppType);
					bIsSet = true;
				}
			}
			
			if (!bIsSet)
			{
				StringBuilder.Append(ByteProperty->GetCPPType());
			}
		}
		else
		{
			StringBuilder.Append(Property->GetCPPType());
		}

		if (Property->IsA(FStrProperty::StaticClass()))
		{
			if (bShouldConst && !Property->HasAnyPropertyFlags(CPF_ConstParm))
			{
				StringBuilder.Append(TEXT("&"));
			}
		}
		else if (Property->HasAnyPropertyFlags(CPF_ReferenceParm) && Property->HasAnyPropertyFlags(CPF_ConstParm))
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

		bool bIsInterfaceProp = Property->IsA(FInterfaceProperty::StaticClass());

		// When do we need a leading const:
		// 1) If this is a object or object ptr property and the referenced class is const
		// 2) If this is not an out parameter or reference parameter then,
		// if this is a parameter
		// AND - if this is a const param OR (if this is an interface property and not an out param)
		// 3) If this is a parameter without array dimensions, must be passed by reference, but not an out parameter or const param
		bool bPassCppArgsByRef = GetIsPassCppArgsByRef(Property);

		bool bIsConstParam = Property->HasAnyPropertyFlags(CPF_ConstParm)
				|| (bIsInterfaceProp && !Property->HasAnyPropertyFlags(CPF_OutParm));

		bool bIsConstArgsByRef = Property->HasAnyPropertyFlags(CPF_Parm) && Property->ArrayDim <= 1 && bPassCppArgsByRef && !Property->HasAnyPropertyFlags(CPF_ConstParm | CPF_OutParm);

		bool bIsOnConstClass = false;

		if (const auto ObjectProperty = Cast<FObjectProperty>(Property))
		{
			bIsOnConstClass = ObjectProperty->PropertyClass->HasAnyClassFlags(CLASS_Const) || !ObjectProperty->PropertyClass->GetMetaData(TEXT("NativeConst")).IsEmpty();
		}

		bool bShouldHaveRef = Property->HasAnyPropertyFlags(CPF_OutParm | CPF_ReferenceParm);

		bool bConstAtTheBeginning = bIsOnConstClass || bIsConstArgsByRef || (bIsConstParam && !bShouldHaveRef);

		if (bConstAtTheBeginning)
		{
			if (Property->IsA(FArrayProperty::StaticClass())
				|| Property->IsA(FInterfaceProperty::StaticClass())
				|| Property->IsA(FSoftObjectProperty::StaticClass()))
			{
				if (Property->HasAnyPropertyFlags(CPF_ReferenceParm) && Property->HasAnyPropertyFlags(CPF_ConstParm))
				{
					StringBuilder.Append(TEXT("const "));
				}
			}
			else
			{
				StringBuilder.Append(TEXT("const "));
			}
		}

		if (const auto EnumProperty = Cast<FEnumProperty>(Property))
		{
			StringBuilder.Append(EnumProperty->GetCPPType(nullptr, 0));
		}
		else if (const auto ByteProperty = Cast<FByteProperty>(Property))
		{
			StringBuilder.Append(ByteProperty->GetCPPType());
			/*bool bIsSet = false;
			
			if (ByteProperty->GetIntPropertyEnum() != nullptr)
			{
				if (!ByteProperty->GetIntPropertyEnum()->CppType.IsEmpty())
				{
					StringBuilder.Append(ByteProperty->GetIntPropertyEnum()->CppType);
					bIsSet = true;
				}
			}
			
			if (!bIsSet)
			{
				StringBuilder.Append(ByteProperty->GetCPPType());
			}*/
		}
		else if (const auto ArrayProperty = Cast<FArrayProperty>(Property))
		{
			StringBuilder.Append(TEXT("TArray<"));
			StringBuilder.Append(GetParamPropertySignature(ArrayProperty->Inner));
			StringBuilder.Append(TEXT(">"));
		}
		else
		{
			StringBuilder.Append(Property->GetCPPType());
		}

		bool bFromConstClass = false;

		if (const auto OuterClass = Property->GetOwnerClass())
		{
			bFromConstClass = OuterClass->HasAnyClassFlags(CLASS_Const);
		}

		bool bConstAtTheEnd = bFromConstClass || (bIsConstParam && bShouldHaveRef);

		if (bConstAtTheEnd)
		{
			if (Property->IsA(FArrayProperty::StaticClass())
				|| Property->IsA(FInterfaceProperty::StaticClass())
				|| Property->IsA(FSoftObjectProperty::StaticClass()))
			{
				if (Property->HasAnyPropertyFlags(CPF_ReferenceParm) && Property->HasAnyPropertyFlags(CPF_ConstParm))
				{
					StringBuilder.Append(TEXT(" const"));
				}
			}
			else
			{
				StringBuilder.Append(TEXT(" const"));
			}
		}

		bShouldHaveRef = bPassCppArgsByRef;

		if (bShouldHaveRef
			|| Property->ArrayDim <= 1
			&& (bPassCppArgsByRef || Property->HasAnyPropertyFlags(CPF_OutParm | CPF_ReferenceParm))
			)
		{
			if (Property->IsA(FArrayProperty::StaticClass())
				|| Property->IsA(FStrProperty::StaticClass())
				|| Property->IsA(FTextProperty::StaticClass())
				|| Property->IsA(FInterfaceProperty::StaticClass())
				|| Property->IsA(FSoftObjectProperty::StaticClass()))
			{
				if (Property->HasAnyPropertyFlags(CPF_OutParm))
				{
					StringBuilder.Append(TEXT("&"));
				}
				else if (Property->IsA(FStrProperty::StaticClass()))
				{
					if (Property->HasMetaData(TEXT("NativeConst")) && !Property->HasAnyPropertyFlags(CPF_ConstParm))
					{
						StringBuilder.Append(TEXT("&"));
					}
				}
			}
			else
			{
				StringBuilder.Append(TEXT("&"));
			}
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
			SignatureBuilder.Append(FString::Printf(TEXT("(%s::*)"), *(Class->GetPrefixCPP() + Class->GetName())));
		}

		SignatureBuilder.Append("(");

		bool bIsHasProperty = false;

		for (TFieldIterator<FProperty> It(Function); It; ++It)
		{
			if (!It->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				SignatureBuilder.Append(GetParamPropertySignature(*It));

				SignatureBuilder.Append(TEXT(", "));

				bIsHasProperty = true;
			}
		}

		if (bIsHasProperty)
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
				Builder.Append(FString::Printf(TEXT("\"%s\", "), *It->GetName()));

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
					if (!ValueStr.IsEmpty())
					{
						Builder.Append(", ");
					
						if (ValueStr == "NULL")
						{
							Builder.Append("nullptr");
						}
						else if (ValueStr.Equals("None") && It->IsA(FNameProperty::StaticClass()))
						{
							Builder.Append("NAME_None");
						}
						else if (const auto EnumProperty = Cast<FEnumProperty>(*It))
						{
							Builder.Append(FString::Printf(TEXT("%s::%s"),
								*EnumProperty->GetEnum()->CppType,
								*ValueStr));
						}
						else
						{
							Builder.Append(ValueStr);
						}
					}
				}
			}
		}

		return Builder;
	}

	FString GetHeaderFile(UClass* InClass)
	{
		return FPaths::Combine(HeaderPath.FindRef(FPaths::GetCleanFilename( InClass->GetPackage()->GetName() ) ), InClass->GetMetaData("ModuleRelativePath"));
	}

	static FString GenerateInclude(FString File)
	{
		return FString::Printf(TEXT("#include \"%s\"\n"), *File);
	}

	FString GetInclude(UClass* InClass)
	{
		return GenerateInclude(GetHeaderFile(InClass));
	}
	
	void GetPlugins(FString InPathName, TMap<FString, FString>& Plugins)
    {
        FString Suffix = FString::Printf(TEXT("*.uplugin"));

		IFileManager& MyFileManager = IFileManager::Get();
		if (MyFileManager.DirectoryExists(*InPathName))
		{
			TArray<FString> FileNames;
			MyFileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);
			for (auto& PluginName : FileNames)
			{
				Plugins.Add(FPaths::GetCleanFilename(PluginName).Left(FPaths::GetCleanFilename(PluginName).Len() - Suffix.Len() + 1), FPaths::ConvertRelativePathToFull(FPaths::GetPath(PluginName)));
			}
		}
    }
	
	void GetModules(FString InPathName, TMap<FString, FString>& Modules)
	{
		FString Suffix = FString::Printf(TEXT("*.Build.cs"));

		IFileManager& MyFileManager = IFileManager::Get();
		if (MyFileManager.DirectoryExists(*InPathName))
		{
			TArray<FString> FileNames;
			MyFileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);
			for (auto& PluginName : FileNames)
			{
				Modules.Add(FPaths::GetCleanFilename(PluginName).Left(FPaths::GetCleanFilename(PluginName).Len() - Suffix.Len() + 1), FPaths::ConvertRelativePathToFull(FPaths::GetPath(PluginName)));
			}
		}
	}

	void GetModules(FString InPathName, TSet<FString>& Modules)
	{
		FString Suffix = FString::Printf(TEXT("*.Build.cs"));

		IFileManager& MyFileManager = IFileManager::Get();
		if (MyFileManager.DirectoryExists(*InPathName))
		{
			TArray<FString> FileNames;
			MyFileManager.FindFilesRecursive(FileNames, *InPathName, *Suffix, true, false);
			for (auto& PluginName : FileNames)
			{
				Modules.Add(FPaths::GetCleanFilename(PluginName).Left(FPaths::GetCleanFilename(PluginName).Len() - Suffix.Len() + 1));
			}
		}
	}

	void ParseModule(const FString& ModuleName, EBuildModuleType::Type ModuleType, const FString& ModuleGeneratedIncludeDirectory)
	{
		if (ModuleType == EBuildModuleType::GameRuntime)
		{
			// For Only Game Project has GameRuntime Module, this should be Game Project
			HasGameRuntime = true;
		}
	}

public:
	bool HasGameRuntime; // Flag for if current uht has GameRuntime module or not
	
	FString OutputDir;
	
	FString ProjectPath;

	FString ProjectSourcePath;

	FString ProjectPluginsPath;

	FString EngineSourcePath;

	FString EnginePluginsPath;

	TArray<FString> ExportModules;
	
	TSet<FString> Project;

	TMap<FString, FString> HeaderPath;

	TMap<FString, TArray<FString>> ModuleHeaderPath;

	const FString BindingSuffix = FString::Printf(TEXT(".binding.inl"));

	const FString HeaderSuffix = FString::Printf(TEXT(".header.inl"));

public:
	TSet<FString> SupportedTypes;

	void AddSupportedType(const FString Type)
	{
		SupportedTypes.Add(Type);
	}
};

#undef GET_ZERO_DEFAULT_VALUE
#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FSourceCodeGeneratorUbtPluginModule, SourceCodeGeneratorUbtPlugin)