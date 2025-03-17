#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Misc/FileHelper.h"
#include "Containers/ArrayBuilder.h"
#include "Common/NameEncode.h"
#include "Domain/AssemblyLoader.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Interfaces/IPluginManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "Setting/UnrealCSharpSetting.h"
#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#endif

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetDotNet()
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefaultSafe<UUnrealCSharpEditorSetting>())
	{
		if (const auto& DotNetPath = UnrealCSharpEditorSetting->GetDotNetPath(); !DotNetPath.IsEmpty())
		{
			return DotNetPath;
		}
	}

#if PLATFORM_WINDOWS
	return TEXT("C:/Program Files/dotnet/dotnet.exe");
#else
	return TEXT("/usr/local/share/dotnet/dotnet");
#endif
}
#endif

FString FUnrealCSharpFunctionLibrary::GetModuleName(const UField* InField)
{
	return InField ? GetModuleName(InField->GetPackage()) : FString();
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(const UField* InField)
{
	if (InField == nullptr)
	{
		return FString();
	}

	const auto Package = InField->GetPackage();

	if (Package == nullptr)
	{
		return FString();
	}

	auto ModuleRelativePath = FPaths::Combine(GetOuterRelativePath(Package->GetName()),
	                                          GetModuleRelativePathMetaData(InField));

	if (!InField->IsNative())
	{
		ProcessModuleRelativePath(ModuleRelativePath);
	}

	return ModuleRelativePath;
}

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePathMetaData(const UField* InField)
{
	FString ModuleRelativePathMetaData;

	if (InField == nullptr)
	{
		return ModuleRelativePathMetaData;
	}

	ModuleRelativePathMetaData = FPaths::GetPath(InField->GetMetaData(TEXT("ModuleRelativePath")));

	return ProcessModuleRelativePathMetaData(ModuleRelativePathMetaData);
}
#endif

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetModuleName(
#if UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR
	const TObjectPtr<UFunction>& InSignatureFunction)
#else
	const UFunction* InSignatureFunction)
#endif
{
	FString ModuleName;

	if (InSignatureFunction == nullptr || InSignatureFunction->GetOuter() == nullptr)
	{
		return ModuleName;
	}

	if (InSignatureFunction->GetOuter()->IsA<UClass>())
	{
		ModuleName = GetModuleName(GetOuterName(InSignatureFunction));
	}
	else if (const auto Package = Cast<UPackage>(InSignatureFunction->GetOuter()))
	{
		ModuleName = GetModuleName(Package);
	}

	return ModuleName;
}
#endif

FString FUnrealCSharpFunctionLibrary::GetModuleName(const UPackage* InPackage)
{
	if (InPackage == nullptr)
	{
		return FString();
	}

	if (const auto Name = InPackage->GetName();
		!Name.IsEmpty())
	{
		return GetModuleName(Name);
	}

	return FString();
}

FString FUnrealCSharpFunctionLibrary::GetModuleName(const FString& InName)
{
	FString ModuleName;

	if (InName.IsEmpty())
	{
		return ModuleName;
	}

	TArray<FString> OutArray;

	InName.ParseIntoArray(OutArray, TEXT("/"));

	if (const auto& ProjectModuleList = GetProjectModuleList();
		ProjectModuleList.Contains(OutArray[0]) ||
		OutArray[0] == TEXT("Game") ||
		(OutArray[0] == TEXT("Script") && ProjectModuleList.Contains(OutArray[1])))
	{
		ModuleName = FApp::GetProjectName();
	}
	else if (OutArray.IsValidIndex(1))
	{
		ModuleName = OutArray[1];
	}

	return ModuleName;
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(
	const FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return FString();
	}

	const auto SignatureFunction = InDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return FString();
	}

	auto ModuleRelativePath = FPaths::Combine(GetOuterRelativePath(SignatureFunction),
	                                          GetModuleRelativePathMetaData(InDelegateProperty));

	if (!InDelegateProperty->IsNative())
	{
		ProcessModuleRelativePath(ModuleRelativePath);
	}

	return ModuleRelativePath;
}

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePathMetaData(
	const FDelegateProperty* InDelegateProperty)
{
	FString ModuleRelativePathMetaData;

	if (InDelegateProperty == nullptr)
	{
		return ModuleRelativePathMetaData;
	}

	ModuleRelativePathMetaData = FPaths::GetPath(InDelegateProperty->GetMetaData(TEXT("ModuleRelativePath")));

	return ProcessModuleRelativePathMetaData(ModuleRelativePathMetaData);
}

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(
	const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return FString();
	}

	const auto SignatureFunction = InMulticastDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return FString();
	}

	auto ModuleRelativePath = FPaths::Combine(GetOuterRelativePath(SignatureFunction),
	                                          GetModuleRelativePathMetaData(InMulticastDelegateProperty));

	if (!InMulticastDelegateProperty->IsNative())
	{
		ProcessModuleRelativePath(ModuleRelativePath);
	}

	return ModuleRelativePath;
}

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePathMetaData(
	const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	FString ModuleRelativePathMetaData;

	if (InMulticastDelegateProperty == nullptr)
	{
		return ModuleRelativePathMetaData;
	}

	ModuleRelativePathMetaData = FPaths::GetPath(InMulticastDelegateProperty->GetMetaData(TEXT("ModuleRelativePath")));

	return ProcessModuleRelativePathMetaData(ModuleRelativePathMetaData);
}

void FUnrealCSharpFunctionLibrary::ProcessModuleRelativePath(FString& OutModuleRelativePath)
{
	if (!OutModuleRelativePath.IsEmpty())
	{
		OutModuleRelativePath.RemoveFromEnd(TEXT("/"));

		if (auto Index = 0; OutModuleRelativePath.FindLastChar(TEXT('/'), Index))
		{
			OutModuleRelativePath.LeftInline(Index);
		}
	}
}
#endif

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetOuterRelativePath(
#if UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR
	const TObjectPtr<UFunction>& InSignatureFunction)
#else
	const UFunction* InSignatureFunction)
#endif
{
	return InSignatureFunction ? GetOuterRelativePath(GetOuterName(InSignatureFunction)) : FString();
}

FString FUnrealCSharpFunctionLibrary::GetOuterRelativePath(const FString& InRelativePath)
{
	FString OuterRelativePath;

	if (InRelativePath.IsEmpty())
	{
		return OuterRelativePath;
	}

	TArray<FString> OutArray;

	InRelativePath.ParseIntoArray(OutArray, TEXT("/"));

	if (const auto& ProjectModuleList = GetProjectModuleList();
		ProjectModuleList.Contains(OutArray[0]) || OutArray[0] == TEXT("Game"))
	{
		OuterRelativePath = InRelativePath.RightChop(OutArray[0].Len() + 1);
	}
	else if (OutArray.IsValidIndex(1))
	{
		if (const auto Index = InRelativePath.Find(OutArray[1]);
			Index != INDEX_NONE)
		{
			OuterRelativePath = InRelativePath.RightChop(Index + OutArray[1].Len());
		}
	}

	return OuterRelativePath;
}

FString FUnrealCSharpFunctionLibrary::GetOuterName(
#if UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR
	const TObjectPtr<UFunction>& InSignatureFunction)
#else
	const UFunction* InSignatureFunction)
#endif
{
	FString OuterName;

	if (InSignatureFunction == nullptr)
	{
		return OuterName;
	}

	if (const auto Class = Cast<UClass>(InSignatureFunction->GetOuter()))
	{
		OuterName = GetOuterName(Class);
	}
	else if (const auto Package = Cast<UPackage>(InSignatureFunction->GetOuter()))
	{
		OuterName = GetOuterName(Package);
	}

	return OuterName;
}

FString FUnrealCSharpFunctionLibrary::GetOuterName(const UPackage* InPackage)
{
	return InPackage ? InPackage->GetName() : FString();
}

FString FUnrealCSharpFunctionLibrary::GetOuterName(const UClass* InClass)
{
	FString OuterName;

	if (InClass == nullptr)
	{
		return OuterName;
	}

	if (InClass->IsNative())
	{
		OuterName = FString::Printf(TEXT(
			"%s/%s"
		),
		                            *(InClass->GetOuter() ? InClass->GetOuter()->GetName() : TEXT("")),
		                            *InClass->GetName());
	}
	else
	{
		OuterName = *(InClass->GetOuter() ? InClass->GetOuter()->GetName() : TEXT(""));
	}

	return OuterName;
}

FString FUnrealCSharpFunctionLibrary::ProcessModuleRelativePathMetaData(const FString& InModuleRelativePathMetaData)
{
	TArray<FString> OutArray;

	InModuleRelativePathMetaData.ParseIntoArray(OutArray, TEXT("/"));

	OutArray.RemoveAll([](const FString& Element)
	{
		return Element == TEXT("Public") || Element == TEXT("Private");
	});

	return FString::Join(OutArray, TEXT("/"));
}
#endif

FString FUnrealCSharpFunctionLibrary::GetFullClass(const UStruct* InStruct)
{
	if (InStruct == nullptr)
	{
		return TEXT("");
	}

	return Encode(FString::Printf(TEXT(
		              "%s%s"
	              ),
	                              InStruct->IsNative() &&
	                              !FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(InStruct)
		                              ? InStruct->GetPrefixCPP()
		                              : TEXT(""),
	                              *InStruct->GetName()),
	              InStruct->IsNative() &&
	              !FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(InStruct)
	);
}

FString FUnrealCSharpFunctionLibrary::GetFullInterface(const UStruct* InStruct)
{
	return Encode(FString::Printf(TEXT(
		              "I%s"
	              ),
	                              InStruct->IsInBlueprint()
		                              ? *GetFullClass(InStruct)
		                              : *GetFullClass(InStruct).RightChop(1)),
	              InStruct->IsInBlueprint()
	);
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UStruct* InStruct)
{
	if (InStruct == nullptr)
	{
		return TEXT("");
	}

	auto ModuleName = InStruct->GetOuter() ? InStruct->GetOuter()->GetName() : TEXT("");

	if (InStruct->IsNative())
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}
	else
	{
		if (auto Index = 0; ModuleName.FindLastChar(TEXT('/'), Index))
		{
			ModuleName = ModuleName.Left(Index);
		}
	}

	TArray<FString> Splits;

	ModuleName.ParseIntoArray(Splits, TEXT("/"));

	FNameEncode::Encode(Splits);

	ModuleName = FString::Join(Splits, TEXT("."));

	return FString::Printf(TEXT(
		"%s.%s"
	),
	                       *NAMESPACE_SCRIPT,
	                       *ModuleName);
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UClass* InClass)
{
	return FDynamicGenerator::IsDynamicClass(InClass)
		       ? FDynamicGenerator::GetNameSpace(InClass)
		       : GetClassNameSpace(static_cast<const UStruct*>(InClass));
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UScriptStruct* InScriptStruct)
{
	return FDynamicGenerator::IsDynamicStruct(InScriptStruct)
		       ? FDynamicGenerator::GetNameSpace(InScriptStruct)
		       : GetClassNameSpace(static_cast<const UStruct*>(InScriptStruct));
}

FString FUnrealCSharpFunctionLibrary::GetFullClass(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return TEXT("");
	}

	return Encode(InEnum->GetName(), InEnum->IsNative());
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return TEXT("");
	}

	if (FDynamicGenerator::IsDynamicEnum(InEnum))
	{
		return FDynamicGenerator::GetNameSpace(InEnum);
	}

	FString ModuleName = InEnum->GetOuter() ? InEnum->GetOuter()->GetName() : TEXT("");

	if (InEnum->IsNative())
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}
	else
	{
		ModuleName = ModuleName.Replace(*FString::Printf(TEXT(
			                                "/%s"
		                                ),
		                                                 *InEnum->GetName()),
		                                TEXT(""));
	}

	return FString::Printf(TEXT(
		"%s%s"
	),
	                       *NAMESPACE_SCRIPT,
	                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
}

FString FUnrealCSharpFunctionLibrary::GetFullClass(const FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	auto DelegateName = SignatureFunction->GetName();

	DelegateName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(),
#if UE_F_STRING_LEFT_CHOP_IN_LINE_E_ALLOW_SHRINKING
	                            EAllowShrinking::No
#else
	                            false
#endif
	);

	return Encode(FString::Printf(TEXT(
		              "F%s"
	              ),
	                              *DelegateName),
	              InDelegateProperty->IsNative());
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
	{
		return FString::Printf(TEXT(
			"%s.%s"
		),
		                       *GetClassNameSpace(Class),
		                       *Class->GetName());
	}

	if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
	{
		const auto ModuleName = Package->GetName().Replace(TEXT("/Script/"), TEXT("/"));

		return FString::Printf(TEXT(
			"%s%s"
		),
		                       *NAMESPACE_SCRIPT,
		                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
	}

	return TEXT("");
}

FString FUnrealCSharpFunctionLibrary::GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InMulticastDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	auto DelegateName = SignatureFunction->GetName();

	DelegateName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(),
#if UE_F_STRING_LEFT_CHOP_IN_LINE_E_ALLOW_SHRINKING
	                            EAllowShrinking::No
#else
	                            false
#endif
	);

	return Encode(FString::Printf(TEXT(
		              "F%s"
	              ),
	                              *DelegateName),
	              InMulticastDelegateProperty->IsNative());
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InMulticastDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
	{
		if (InMulticastDelegateProperty->IsNative())
		{
			return FString::Printf(TEXT(
				"%s.%s"
			),
			                       *GetClassNameSpace(Class),
			                       *Class->GetName());
		}
		else
		{
			return *GetClassNameSpace(Class);
		}
	}

	if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
	{
		const auto ModuleName = Package->GetName().Replace(TEXT("/Script/"), TEXT("/"));

		return FString::Printf(TEXT(
			"%s%s"
		),
		                       *NAMESPACE_SCRIPT,
		                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
	}

	return TEXT("");
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetSuffixName(const FAssetData& InAssetData)
{
	return InAssetData.GetClass()->GetFName() == UBlueprint::StaticClass()->GetFName() ||
	       InAssetData.GetClass()->GetFName() == UWidgetBlueprint::StaticClass()->GetFName() ||
	       InAssetData.GetClass()->GetFName() == UAnimBlueprint::StaticClass()->GetFName()
		       ? TEXT("_C")
		       : TEXT("");
}

FString FUnrealCSharpFunctionLibrary::GetAssetName(const FAssetData& InAssetData, const FString& InAssetName)
{
	return FString::Printf(TEXT(
		"%s%s"
	),
	                       *Encode(InAssetName, false),
	                       *GetSuffixName(InAssetData)
	);
}

FString FUnrealCSharpFunctionLibrary::GetObjectPathName(const FAssetData& InAssetData, const FString& InObjectPathName)
{
	return FString::Printf(TEXT(
		"%s%s"
	),
	                       *InObjectPathName,
	                       *GetSuffixName(InAssetData)
	);
}

FString FUnrealCSharpFunctionLibrary::GetAssetClass(const FAssetData& InAssetData, const FString& InClass)
{
	static TMap<UClass*, FString> AssetClass = {
		{
			UAnimBlueprint::StaticClass(),
			UAnimInstance::StaticClass()->GetPrefixCPP() + UAnimInstance::StaticClass()->GetName()
		}
	};

	return AssetClass.Contains(InAssetData.GetClass()) ? AssetClass[InAssetData.GetClass()] : InClass;
}

FString FUnrealCSharpFunctionLibrary::GetFileName(const FAssetData& InAssetData)
{
	return GetFileName(InAssetData, InAssetData.AssetName.ToString());
}

FString FUnrealCSharpFunctionLibrary::GetFileName(const FAssetData& InAssetData, const FString& InAssetName)
{
	auto ModuleName = InAssetData.PackagePath.ToString().Replace(TEXT("Game"), FApp::GetProjectName());

	auto DirectoryName = FPaths::Combine(GetGenerationPath(ModuleName), ModuleName);

	return FPaths::Combine(DirectoryName, GetAssetName(InAssetData, InAssetName) + CSHARP_SUFFIX);
}

FString FUnrealCSharpFunctionLibrary::GetOldFileName(const FAssetData& InAssetData, const FString& InOldObjectPath)
{
	return GetFileName(InAssetData, InOldObjectPath.Right(InOldObjectPath.Len() - InOldObjectPath.Find(TEXT(".")) - 1));
}
#endif

FString FUnrealCSharpFunctionLibrary::GetUEName()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetUEName();
	}

	return DEFAULT_UE_NAME;
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetUEDirectory()
{
	return GetFullScriptDirectory() / GetUEName();
}

FString FUnrealCSharpFunctionLibrary::GetUEProxyDirectory()
{
	return GetUEDirectory() / PROXY_NAME;
}

FString FUnrealCSharpFunctionLibrary::GetUEProjectPath()
{
	return GetUEDirectory() / GetUEName() + PROJECT_SUFFIX;
}
#endif

FString FUnrealCSharpFunctionLibrary::GetGameName()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetGameName();
	}

	return DEFAULT_GAME_NAME;
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetGameDirectory()
{
	return GetFullScriptDirectory() / GetGameName();
}

FString FUnrealCSharpFunctionLibrary::GetGameProxyDirectory()
{
	return GetGameDirectory() / PROXY_NAME;
}

FString FUnrealCSharpFunctionLibrary::GetGameProjectPath()
{
	return GetGameDirectory() / GetGameName() + PROJECT_SUFFIX;
}

FString FUnrealCSharpFunctionLibrary::GetGameProjectPropsPath()
{
	return GetGameDirectory() / GetGameName() + PROJECT_PROPS_SUFFIX;
}
#endif

#if WITH_EDITOR
TArray<FString> FUnrealCSharpFunctionLibrary::GetCustomProjectsName()
{
	TArray<FString> CustomProjectsName;

	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		for (const auto& [Name] : UnrealCSharpSetting->GetCustomProjects())
		{
			CustomProjectsName.Add(Name);
		}
	}

	return CustomProjectsName;
}

TArray<FString> FUnrealCSharpFunctionLibrary::GetCustomProjectsDirectory()
{
	TArray<FString> CustomProjectsDirectory;

	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		for (const auto& [Name] : UnrealCSharpSetting->GetCustomProjects())
		{
			CustomProjectsDirectory.Add(GetFullScriptDirectory() / Name);
		}
	}

	return CustomProjectsDirectory;
}
#endif

#if WITH_EDITOR
bool FUnrealCSharpFunctionLibrary::IsRootPath(const FString& InPath)
{
	if (InPath.StartsWith(GetGameDirectory()))
	{
		return true;
	}

	for (const auto& CustomProjectsDirectory : GetCustomProjectsDirectory())
	{
		if (InPath.StartsWith(CustomProjectsDirectory))
		{
			return true;
		}
	}

	return false;
}
#endif

bool FUnrealCSharpFunctionLibrary::EnableCallOverrideFunction()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->EnableCallOverrideFunction();
	}

	return false;
}

FString FUnrealCSharpFunctionLibrary::GetOverrideFunctionNamePrefix()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetOverrideFunctionNamePrefix();
	}

	return DEFAULT_OVERRIDE_FUNCTION_NAME_PREFIX;
}

FString FUnrealCSharpFunctionLibrary::GetOverrideFunctionNameSuffix()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetOverrideFunctionNameSuffix();
	}

	return DEFAULT_OVERRIDE_FUNCTION_NAME_SUFFIX;
}

FString FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(const FString& InFunctionName)
{
	return FString::Printf(TEXT(
		"%s%s%s"
	),
	                       *GetOverrideFunctionNamePrefix(),
	                       *InFunctionName,
	                       *GetOverrideFunctionNameSuffix()
	);
}

FString FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(const FName& InFunctionName)
{
	return FString::Printf(TEXT(
		"%s%s%s"
	),
	                       *GetOverrideFunctionNamePrefix(),
	                       *InFunctionName.ToString(),
	                       *GetOverrideFunctionNameSuffix()
	);
}

FString FUnrealCSharpFunctionLibrary::GetBindingDirectory()
{
	return BINDING_NAME;
}

FString FUnrealCSharpFunctionLibrary::GetPluginBaseDir()
{
	return IPluginManager::Get().FindPlugin(PLUGIN_NAME)->GetBaseDir();
}

FString FUnrealCSharpFunctionLibrary::GetPluginDirectory()
{
	return FPaths::ConvertRelativePathToFull(GetPluginBaseDir());
}

FString FUnrealCSharpFunctionLibrary::GetPluginScriptDirectory()
{
	return GetPluginDirectory() / PLUGIN_SCRIPT_PATH;
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetPluginTemplateDirectory()
{
	return GetPluginDirectory() / PLUGIN_TEMPLATE_PATH;
}

FString FUnrealCSharpFunctionLibrary::GetPluginTemplateOverrideDirectory()
{
	return GetPluginTemplateDirectory() / PLUGIN_TEMPLATE_OVERRIDE;
}

FString FUnrealCSharpFunctionLibrary::GetPluginTemplateOverrideFileName(const UClass* InClass)
{
	return GetPluginTemplateOverrideDirectory() /
		FString::Printf(TEXT(
			"%s%s"
		),
		                *InClass->GetName(),
		                *CSHARP_SUFFIX);
}

FString FUnrealCSharpFunctionLibrary::GetPluginTemplateDynamicDirectory()
{
	return GetPluginTemplateDirectory() / PLUGIN_TEMPLATE_DYNAMIC;
}

FString FUnrealCSharpFunctionLibrary::GetPluginTemplateDynamicFileName(const UClass* InClass)
{
	return GetPluginTemplateDynamicDirectory() /
		FString::Printf(TEXT(
			"%s%s%s"
		),
		                *DYNAMIC_CLASS_DEFAULT_PREFIX,
		                *InClass->GetName(),
		                *CSHARP_SUFFIX);
}
#endif

bool FUnrealCSharpFunctionLibrary::IsGameField(const UField* InField)
{
	const auto ModuleName = GetModuleName(InField);

	if (const auto Module = FModuleManager::Get().GetModule(*ModuleName))
	{
		return Module->IsGameModule();
	}

	if (const auto Plugin = IPluginManager::Get().FindPlugin(ModuleName))
	{
		return Plugin->GetType() == EPluginType::Project;
	}

	return false;
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetGenerationPath(const UField* InField)
{
	if (InField == nullptr || InField->GetPackage() == nullptr)
	{
		return TEXT("");
	}

	return GetGenerationPath(InField->GetPackage()->GetName());
}

FString FUnrealCSharpFunctionLibrary::GetGenerationPath(const FString& InScriptPath)
{
	if (InScriptPath.IsEmpty() || !InScriptPath.StartsWith(TEXT("/")))
	{
		return TEXT("");
	}

	TArray<FString> Splits;

	InScriptPath.ParseIntoArray(Splits, TEXT("/"));

	if (const auto& ProjectModuleList = GetProjectModuleList();
		ProjectModuleList.Contains(Splits[0]) ||
		Splits[0] == TEXT("Game") ||
		(Splits[0] == NAMESPACE_SCRIPT &&
			ProjectModuleList.Contains(Splits[1])))
	{
		static auto GameProxyPath = GetGameProxyDirectory();

		return GameProxyPath;
	}
	else
	{
		static auto UEProxyPath = GetUEProxyDirectory();

		return UEProxyPath;
	}
}
#endif

FString FUnrealCSharpFunctionLibrary::GetPublishDirectory()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetPublishDirectory();
	}

	return DEFAULT_PUBLISH_DIRECTORY;
}

FString FUnrealCSharpFunctionLibrary::GetFullPublishDirectory()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() / GetPublishDirectory());
}

FString FUnrealCSharpFunctionLibrary::GetFullUEPublishPath()
{
	return GetFullPublishDirectory() / GetUEName() + DLL_SUFFIX;
}

FString FUnrealCSharpFunctionLibrary::GetFullGamePublishPath()
{
	return GetFullPublishDirectory() / GetGameName() + DLL_SUFFIX;
}

TArray<FString> FUnrealCSharpFunctionLibrary::GetFullCustomProjectsPublishPath()
{
	TArray<FString> FullCustomProjectsPublishPath;

	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		for (const auto& [Name] : UnrealCSharpSetting->GetCustomProjects())
		{
			FullCustomProjectsPublishPath.Add(GetFullPublishDirectory() / Name + DLL_SUFFIX);
		}
	}

	return FullCustomProjectsPublishPath;
}

TArray<FString> FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath()
{
	return TArrayBuilder<FString>().
	       Add(GetFullUEPublishPath()).
	       Add(GetFullGamePublishPath()).
	       Append(GetFullCustomProjectsPublishPath()).
	       Build();
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetScriptDirectory()
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefaultSafe<UUnrealCSharpEditorSetting>())
	{
		return UnrealCSharpEditorSetting->GetScriptDirectory();
	}

	return DEFAULT_SCRIPT_DIRECTORY;
}

FString FUnrealCSharpFunctionLibrary::GetFullScriptDirectory()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / GetScriptDirectory());
}

FString FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath()
{
	return GetFullScriptDirectory() / CODE_ANALYSIS_NAME;
}

FString FUnrealCSharpFunctionLibrary::GetCodeAnalysisProjectPath()
{
	return GetCodeAnalysisCSProjPath() / CODE_ANALYSIS_NAME + PROJECT_SUFFIX;
}

FString FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()
{
	return FPaths::ProjectIntermediateDir() / CODE_ANALYSIS_NAME;
}

FString FUnrealCSharpFunctionLibrary::GetSourceGeneratorPath()
{
	return GetFullScriptDirectory() / SOURCE_GENERATOR_NAME;
}

FString FUnrealCSharpFunctionLibrary::GetWeaversPath()
{
	return GetFullScriptDirectory() / WEAVERS_NAME;
}
#endif

#if WITH_EDITOR
bool FUnrealCSharpFunctionLibrary::IsGenerateFunctionComment()
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefaultSafe<UUnrealCSharpEditorSetting>())
	{
		return UnrealCSharpEditorSetting->IsGenerateFunctionComment();
	}

	return false;
}
#endif

UAssemblyLoader* FUnrealCSharpFunctionLibrary::GetAssemblyLoader()
{
	if (const auto UnrealCSharpSetting = GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetAssemblyLoader();
	}

	return nullptr;
}

bool FUnrealCSharpFunctionLibrary::SaveStringToFile(const FString& InFileName, const FString& InString)
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (const auto DirectoryName = FPaths::GetPath(InFileName);
		!PlatformFile.DirectoryExists(*DirectoryName))
	{
		PlatformFile.CreateDirectoryTree(*DirectoryName);
	}

	const auto FileManager = &IFileManager::Get();

	return FFileHelper::SaveStringToFile(InString, *InFileName, FFileHelper::EEncodingOptions::ForceUTF8, FileManager,
	                                     FILEWRITE_None);
}

TMap<FString, TArray<FString>> FUnrealCSharpFunctionLibrary::LoadFileToArray(const FString& InFileName)
{
	TMap<FString, TArray<FString>> Result;

	if (auto& FileManager = IFileManager::Get(); FileManager.FileExists(*InFileName))
	{
		if (FString ResultString; FFileHelper::LoadFileToString(ResultString, *InFileName))
		{
			TSharedPtr<FJsonObject> JsonObject;

			const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(ResultString);

			FJsonSerializer::Deserialize(JsonReader, JsonObject);

			for (const auto& [Key, Value] : JsonObject->Values)
			{
				TArray<FString> Array;

				const auto& JsonValueArray = Value->AsArray();

				for (auto Index = 0; Index < JsonValueArray.Num(); Index++)
				{
					if (FString Element; JsonValueArray[Index]->TryGetString(Element))
					{
						Array.Add(Element);
					}
				}

				Result.Add(Key, Array);
			}
		}
	}

	return Result;
}

TMap<FString, FString> FUnrealCSharpFunctionLibrary::LoadFileToString(const FString& InFileName)
{
	TMap<FString, FString> Result;

	if (auto& FileManager = IFileManager::Get(); FileManager.FileExists(*InFileName))
	{
		if (FString ResultString; FFileHelper::LoadFileToString(ResultString, *InFileName))
		{
			TSharedPtr<FJsonObject> JsonObject;

			const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(ResultString);

			FJsonSerializer::Deserialize(JsonReader, JsonObject);

			for (const auto& [Key, Value] : JsonObject->Values)
			{
				Result.Add(Key, Value->AsString());
			}
		}
	}

	return Result;
}

#if WITH_EDITOR
TArray<FString> FUnrealCSharpFunctionLibrary::GetChangedDirectories()
{
	return TArrayBuilder<FString>().
	       Add(GetPluginScriptDirectory() / DEFAULT_UE_NAME).
	       Add(GetGameDirectory()).
	       Append(GetCustomProjectsDirectory()).
	       Build();
}
#endif

FString FUnrealCSharpFunctionLibrary::Encode(const FString& InName, const bool bIsNative, const bool bEncodeWideString)
{
	static TArray<FString, TInlineAllocator<77>> KeyWords{
		TEXT("abstract"), TEXT("as"),
		TEXT("base"), TEXT("bool"), TEXT("break"), TEXT("byte"),
		TEXT("case"), TEXT("catch"), TEXT("char"), TEXT("checked"), TEXT("class"), TEXT("const"), TEXT("continue"),
		TEXT("decimal"), TEXT("default"), TEXT("delegate"), TEXT("do"), TEXT("double"),
		TEXT("else"), TEXT("enum"), TEXT("event"), TEXT("explicit"), TEXT("extern"),
		TEXT("false"), TEXT("finally"), TEXT("fixed"), TEXT("float"), TEXT("for"), TEXT("foreach"),
		TEXT("goto"),
		TEXT("if"), TEXT("implicit"), TEXT("in"), TEXT("int"), TEXT("interface"), TEXT("internal"), TEXT("is"),
		TEXT("lock"), TEXT("long"),
		TEXT("namespace"), TEXT("new"), TEXT("null"),
		TEXT("object"), TEXT("operator"), TEXT("out"), TEXT("override"),
		TEXT("params"), TEXT("private"), TEXT("protected"), TEXT("public"),
		TEXT("readonly"), TEXT("ref"), TEXT("return"),
		TEXT("sbyte"), TEXT("sealed"), TEXT("short"), TEXT("sizeof"), TEXT("stackalloc"), TEXT("static"),
		TEXT("string"), TEXT("struct"), TEXT("switch"),
		TEXT("this"), TEXT("throw"), TEXT("true"), TEXT("try"), TEXT("typeof"),
		TEXT("uint"), TEXT("ulong"), TEXT("unchecked"), TEXT("unsafe"), TEXT("ushort"), TEXT("using"),
		TEXT("virtual"), TEXT("void"), TEXT("volatile"),
		TEXT("while")
	};

	if (KeyWords.ContainsByPredicate([&](const FString& Name)
	{
		return InName.Equals(Name);
	}))
	{
		return FString::Printf(TEXT("__%s"), *InName);
	}

	return bIsNative ? InName : FNameEncode::Encode(InName, bEncodeWideString);
}

FString FUnrealCSharpFunctionLibrary::Encode(const FProperty* InProperty)
{
	return Encode(InProperty->GetName(), InProperty->IsNative());
}

FString FUnrealCSharpFunctionLibrary::Encode(const UFunction* InFunction)
{
	return Encode(InFunction->GetName(), InFunction->IsNative());
}

const TArray<FString>& FUnrealCSharpFunctionLibrary::GetEngineModuleList()
{
	static TArray<FString> EngineModuleList;

	if (EngineModuleList.IsEmpty())
	{
		static auto FilePath = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("UnrealCSharp_Modules.json"));

		if (FString JsonStr; FFileHelper::LoadFileToString(JsonStr, *FilePath))
		{
			const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

			TSharedPtr<FJsonObject> JsonObj;

			FJsonSerializer::Deserialize(JsonReader, JsonObj);

			if (const TSharedPtr<FJsonObject>* OutObject; JsonObj->TryGetObjectField(TEXT("EngineModules"), OutObject))
			{
				for (const auto& [Key, PLACEHOLDER] : OutObject->Get()->Values)
				{
					EngineModuleList.AddUnique(Key);
				}
			}

			if (const TSharedPtr<FJsonObject>* OutObject; JsonObj->TryGetObjectField(TEXT("EnginePlugins"), OutObject))
			{
				for (const auto& [Key, PLACEHOLDER] : OutObject->Get()->Values)
				{
					EngineModuleList.AddUnique(Key);
				}
			}
		}
	}

	return EngineModuleList;
}

const TArray<FString>& FUnrealCSharpFunctionLibrary::GetProjectModuleList()
{
	static TArray<FString> ProjectModuleList;

	if (ProjectModuleList.IsEmpty())
	{
		static auto FilePath = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("UnrealCSharp_Modules.json"));

		if (FString JsonStr; FFileHelper::LoadFileToString(JsonStr, *FilePath))
		{
			const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

			TSharedPtr<FJsonObject> JsonObj;

			FJsonSerializer::Deserialize(JsonReader, JsonObj);

			if (const TSharedPtr<FJsonObject>* OutObject; JsonObj->TryGetObjectField(TEXT("ProjectModules"), OutObject))
			{
				for (const auto& [Key, PLACEHOLDER] : OutObject->Get()->Values)
				{
					ProjectModuleList.AddUnique(Key);
				}
			}

			if (const TSharedPtr<FJsonObject>* OutObject; JsonObj->TryGetObjectField(TEXT("ProjectPlugins"), OutObject))
			{
				for (const auto& [Key, PLACEHOLDER] : OutObject->Get()->Values)
				{
					ProjectModuleList.AddUnique(Key);
				}
			}
		}
	}

	return ProjectModuleList;
}

#if WITH_EDITOR
bool FUnrealCSharpFunctionLibrary::IsSpecialClass(const UClass* InClass)
{
	if (InClass != nullptr)
	{
		if (const auto ClassName = InClass->GetName();
			ClassName.StartsWith(TEXT("SKEL_")) || ClassName.StartsWith(TEXT("PLACEHOLDER-CLASS")) ||
			ClassName.StartsWith(TEXT("REINST_")) || ClassName.StartsWith(TEXT("TRASHCLASS_")) ||
			ClassName.StartsWith(TEXT("LIVECODING_"))
		)
		{
			return true;
		}
	}

	return false;
}

bool FUnrealCSharpFunctionLibrary::IsSpecialStruct(const UScriptStruct* InScriptStruct)
{
	if (InScriptStruct != nullptr)
	{
		if (const auto StructName = InScriptStruct->GetName();
			StructName.StartsWith(TEXT("STRUCT_REINST_")) || StructName.StartsWith(TEXT("LIVECODING_"))
		)
		{
			return true;
		}
	}

	return false;
}

bool FUnrealCSharpFunctionLibrary::IsSpecialEnum(const UEnum* InEnum)
{
	if (InEnum != nullptr)
	{
		if (const auto EnumName = InEnum->GetName();
			EnumName.StartsWith(TEXT("LIVECODING_"))
		)
		{
			return true;
		}
	}

	return false;
}

bool FUnrealCSharpFunctionLibrary::IsDynamicReInstanceField(const UField* InField)
{
	return InField != nullptr
		       ? InField->GetName().StartsWith(FDynamicGeneratorCore::DynamicReInstanceBaseName())
		       : false;
}
#endif

bool FUnrealCSharpFunctionLibrary::IsNativeFunction(const UClass* InClass, const FName& InFunctionName)
{
	if (InClass == nullptr)
	{
		return false;
	}

	const UFunction* Function{};

	auto OwnerClass = InClass;

	auto Class = InClass;

	while (Class != nullptr)
	{
		for (const auto& Interface : Class->Interfaces)
		{
			if (Interface.Class->FindFunctionByName(InFunctionName, EIncludeSuperFlag::Type::ExcludeSuper))
			{
				return Interface.Class->IsNative();
			}
		}

		if (const auto Result = Class->FindFunctionByName(InFunctionName, EIncludeSuperFlag::Type::ExcludeSuper))
		{
			Function = Result;

			OwnerClass = Class;
		}

		Class = Class->GetSuperClass();
	}

	return Function->IsNative() && OwnerClass->IsNative();
}
