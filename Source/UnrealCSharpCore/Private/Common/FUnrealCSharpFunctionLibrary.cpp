#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Misc/FileHelper.h"
#include "Containers/ArrayBuilder.h"
#include "Common/NameEncode.h"
#include "Domain/AssemblyLoader.h"
#include "Dynamic/FDynamicGeneratorCore.h"
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
#include "UEVersion.h"

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
	if (InField == nullptr)
	{
		return FString();
	}

	return GetModuleName(InField->GetPackage());
}

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(const UField* InField)
{
	if (InField == nullptr)
	{
		return FString();
	}

	auto ModuleRelativePath = GetModuleRelativePath(InField->GetPackage());

	return FPaths::Combine(GetModuleRelativePath(FPaths::GetPath(InField->GetMetaData(TEXT("ModuleRelativePath")))),
	                       ModuleRelativePath);
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

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(const UPackage* InPackage)
{
	if (InPackage == nullptr)
	{
		return FString();
	}

	if (const auto Name = InPackage->GetName();
		!Name.IsEmpty())
	{
		return GetPackageRelativePath(Name);
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
	else
	{
		ModuleName = OutArray[1];
	}

	return ModuleName;
}

FString FUnrealCSharpFunctionLibrary::GetPackageRelativePath(const FString& InRelativePath)
{
	auto ModuleRelativePath = InRelativePath;

	if (InRelativePath.IsEmpty())
	{
		return ModuleRelativePath;
	}

	TArray<FString> OutArray;

	InRelativePath.ParseIntoArray(OutArray, TEXT("/"));

	if (const auto& ProjectModuleList = GetProjectModuleList();
		ProjectModuleList.Contains(OutArray[0]) ||
		OutArray[0] == TEXT("Game") ||
		(OutArray[0] == TEXT("Script") && ProjectModuleList.Contains(OutArray[1])))
	{
		ModuleRelativePath = InRelativePath.RightChop(OutArray[0].Len() + 1);
	}
	else if (OutArray.Num() > 1 && OutArray[0] == TEXT("Script"))
	{
		if (const auto Index = InRelativePath.Find(OutArray[1]);
			Index != INDEX_NONE)
		{
			ModuleRelativePath = InRelativePath.RightChop(Index + OutArray[1].Len());
		}
	}

	return ModuleRelativePath;
}

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(
#if UE_GET_MODULE_RELATIVE_PATH_T_OBJECT_PTR
	const TObjectPtr<UFunction>& InSignatureFunction, const bool bIsNative)
#else
	const UFunction* InSignatureFunction, const bool bIsNative)
#endif
{
	FString ModuleRelativePath;

	if (InSignatureFunction == nullptr)
	{
		return ModuleRelativePath;
	}

	if (const auto Class = Cast<UClass>(InSignatureFunction->GetOuter()))
	{
		if (bIsNative)
		{
			ModuleRelativePath = FString::Printf(TEXT(
				"%s/%s"
			),
			                                     *(Class->GetOuter() ? Class->GetOuter()->GetName() : TEXT("")),
			                                     *Class->GetName());
		}
		else
		{
			ModuleRelativePath = *(Class->GetOuter() ? Class->GetOuter()->GetName() : TEXT(""));
		}

		ModuleRelativePath = GetModuleRelativePath(ModuleRelativePath);
	}
	else if (const auto Package = Cast<UPackage>(InSignatureFunction->GetOuter()))
	{
		ModuleRelativePath = GetModuleRelativePath(Package);
	}

	return ModuleRelativePath;
}

FString FUnrealCSharpFunctionLibrary::GetModuleRelativePath(const FString& InRelativePath)
{
	TArray<FString> OutArray;

	InRelativePath.ParseIntoArray(OutArray, TEXT("/"));

	OutArray.RemoveAll([](const FString& Element)
	{
		return Element == TEXT("Public") || Element == TEXT("Private");
	});

	return FString::Join(OutArray, TEXT("/"));
}

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
