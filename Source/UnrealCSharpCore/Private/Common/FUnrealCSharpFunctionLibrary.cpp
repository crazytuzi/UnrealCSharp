#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Misc/FileHelper.h"
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

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetDotNet()
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>())
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
	return GetModuleName(InField, [InField](FString& InModuleName)
	{
		if (InField->IsNative())
		{
			InModuleName.RightChopInline(1);
		}
		else
		{
			if (auto Index = 0; InModuleName.FindLastChar(TEXT('/'), Index))
			{
				InModuleName.LeftInline(Index);
			}
		}
	});
}

FString FUnrealCSharpFunctionLibrary::GetModuleName(const UField* InField,
                                                    const TFunction<void(FString& InModuleName)>& InGetModuleName)
{
	const auto Package = InField != nullptr ? InField->GetPackage() : nullptr;

	auto ModuleName = Package ? Package->GetName() : TEXT("");

	InGetModuleName(ModuleName);

	return GetModuleName(ModuleName);
}

FString FUnrealCSharpFunctionLibrary::GetModuleName(const FString& InModuleName)
{
	auto ModuleName = InModuleName;

	if (constexpr char ReplaceProjectModuleName[] = "/Game";
		ModuleName.StartsWith(ReplaceProjectModuleName))
	{
		constexpr auto ReplaceProjectModuleNameLength = sizeof(ReplaceProjectModuleName) - 1;

		const auto Size_ModuleName = ModuleName.Len();

		const auto Const_Index = Size_ModuleName - ReplaceProjectModuleNameLength;

		ModuleName = FApp::GetProjectName() + ModuleName.Right(Const_Index);
	}
	else
	{
		ModuleName = ModuleName.Replace(TEXT("Script/"), TEXT(""));
	}

	return ModuleName;
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

	DelegateName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

	return Encode(FString::Printf(TEXT(
		"F%s"
	),
	                              *DelegateName));
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

	DelegateName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

	return Encode(FString::Printf(TEXT(
		"F%s"
	),
	                              *DelegateName));
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
	                       *Encode(InAssetName),
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
	const auto UnrealCSharpSetting = GetMutableDefault<UUnrealCSharpSetting>();

	return UnrealCSharpSetting->IsValidLowLevelFast()
		       ? UnrealCSharpSetting->GetUEName()
		       : DEFAULT_UE_NAME;
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
	const auto UnrealCSharpSetting = GetMutableDefault<UUnrealCSharpSetting>();

	return UnrealCSharpSetting->IsValidLowLevelFast()
		       ? UnrealCSharpSetting->GetGameName()
		       : DEFAULT_GAME_NAME;
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
	const auto UnrealCSharpSetting = GetMutableDefault<UUnrealCSharpSetting>();

	return UnrealCSharpSetting->IsValidLowLevelFast()
		       ? UnrealCSharpSetting->GetPublishDirectory().Path
		       : DEFAULT_PUBLISH_DIRECTORY;
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

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetScriptDirectory()
{
	const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>();

	return UnrealCSharpEditorSetting->IsValidLowLevelFast()
		       ? UnrealCSharpEditorSetting->GetScriptDirectory().Path
		       : DEFAULT_SCRIPT_DIRECTORY;
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

UAssemblyLoader* FUnrealCSharpFunctionLibrary::GetAssemblyLoader()
{
	const auto UnrealCSharpSetting = GetMutableDefault<UUnrealCSharpSetting>();

	return UnrealCSharpSetting->IsValidLowLevelFast()
		       ? UnrealCSharpSetting->GetAssemblyLoader()
		       : nullptr;
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
	static auto UEDirectory = GetPluginScriptDirectory() / DEFAULT_UE_NAME;

	static auto GameDirectory = GetGameDirectory();

	return {UEDirectory, GameDirectory};
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
			ClassName.StartsWith(TEXT("REINST_")) || ClassName.StartsWith(TEXT("TRASHCLASS_")))
		{
			return true;
		}
	}

	return false;
}

bool FUnrealCSharpFunctionLibrary::IsSpecialStruct(const UScriptStruct* InScriptStruct)
{
	return InScriptStruct != nullptr
		       ? InScriptStruct->GetName().StartsWith(TEXT("STRUCT_REINST_"))
		       : false;
}

bool FUnrealCSharpFunctionLibrary::IsDynamicReInstanceField(const UField* InField)
{
	return InField != nullptr
		       ? InField->GetName().StartsWith(FDynamicGeneratorCore::DynamicReInstanceBaseName())
		       : false;
}
#endif
