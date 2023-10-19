#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Misc/FileHelper.h"
#include "Common/NameEncode.h"
#include "Dynamic/CSharpGeneratedClass.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"
#include "Dynamic/CSharpScriptStruct.h"
#include "Dynamic/CSharpEnum.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "UEVersion.h"
#include "Setting/UnrealCSharpEditorSetting.h"

#if WITH_EDITOR
FString FUnrealCSharpFunctionLibrary::GetDotNet()
{
	if (const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>())
	{
		const auto& DotNetPath = UnrealCSharpEditorSetting->GetDotNetPath();

		if (!DotNetPath.IsEmpty())
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
		return TEXT("");
	}

	auto ModuleName = InField->GetOuter() ? InField->GetOuter()->GetName() : TEXT("");

	if (InField->IsNative())
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}
	else
	{
		auto Index = 0;

		if (ModuleName.FindLastChar(TEXT('/'), Index))
		{
			ModuleName = ModuleName.Left(Index);
		}
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
	                              InStruct->IsNative() ? InStruct->GetPrefixCPP() : TEXT(""),
	                              *InStruct->GetName()));
}

FString FUnrealCSharpFunctionLibrary::GetFullInterface(const UStruct* InStruct)
{
	return Encode(FString::Printf(TEXT(
			"I%s"
		),
	                              InStruct->IsInBlueprint()
		                              ? *GetFullClass(InStruct)
		                              : *GetFullClass(InStruct).RightChop(1))
	);
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UStruct* InStruct)
{
	if (InStruct == nullptr)
	{
		return TEXT("");
	}

	auto ModuleName = InStruct->GetOuter() ? InStruct->GetOuter()->GetName() : TEXT("");

	const auto bIsDynamicClass = Cast<UCSharpGeneratedClass>(InStruct) ||
		Cast<UCSharpBlueprintGeneratedClass>(InStruct) ||
		Cast<UCSharpScriptStruct>(InStruct) ||
		UCSharpGeneratedClass::StaticClass() == InStruct ||
		UCSharpBlueprintGeneratedClass::StaticClass() == InStruct ||
		UCSharpScriptStruct::StaticClass() == InStruct;

	if (bIsDynamicClass)
	{
		ModuleName = TEXT("/Script/CoreUObject");
	}

	if (InStruct->IsNative() || bIsDynamicClass)
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}
	else
	{
		auto Index = 0;

		if (ModuleName.FindLastChar(TEXT('/'), Index))
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
	                       TEXT("Script"),
	                       *ModuleName);
}

FString FUnrealCSharpFunctionLibrary::GetFullClass(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return TEXT("");
	}

	return InEnum->GetName();
}

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UEnum* InStruct)
{
	if (InStruct == nullptr)
	{
		return "";
	}

	FString ModuleName = InStruct->GetOuter() ? InStruct->GetOuter()->GetName() : TEXT("");

	if (InStruct->IsNative() || Cast<UCSharpEnum>(InStruct))
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}
	else
	{
		ModuleName = ModuleName.Replace(*FString::Printf(TEXT(
			                                "/%s"
		                                ),
		                                                 *InStruct->GetName()),
		                                TEXT(""));
	}

	return FString::Printf(TEXT(
		"%s%s"
	),
	                       TEXT("Script"),
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

	return FString::Printf(TEXT(
		"F%s"
	),
	                       *DelegateName);
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
		                       *FUnrealCSharpFunctionLibrary::GetClassNameSpace(Class),
		                       *SignatureFunction->GetOuter()->GetName());
	}

	if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
	{
		const auto ModuleName = Package->GetName().Replace(TEXT("/Script/"), TEXT("/"));

		return FString::Printf(TEXT(
			"%s%s"
		),
		                       TEXT("Script"),
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

	return FString::Printf(TEXT(
		"F%s"
	),
	                       *DelegateName);
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
			                       *SignatureFunction->GetOuter()->GetName());
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
		                       TEXT("Script"),
		                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
	}

	return TEXT("");
}

FString FUnrealCSharpFunctionLibrary::GetFileName(const UField* InField)
{
	auto ModuleName = GetModuleName(InField);

	auto DirectoryName = FPaths::Combine(GetGenerationPath(InField), ModuleName);

	return FPaths::ConvertRelativePathToFull(FString::Printf(TEXT(
			"%s.cs"
		),
	                                                         *FPaths::Combine(DirectoryName,
	                                                                          InField->GetName()))
	);
}

FString FUnrealCSharpFunctionLibrary::GetOldFileName(const UField* InField, const FString& OldName)
{
	auto ModuleName = GetModuleName(InField);

	auto DirectoryName = FPaths::Combine(GetGenerationPath(InField), ModuleName);

	return FPaths::ConvertRelativePathToFull(FString::Printf(TEXT(
			"%s.cs"
		),
	                                                         *FPaths::Combine(DirectoryName,
	                                                                          OldName))
	);
}

FString FUnrealCSharpFunctionLibrary::GetBaseName()
{
	return TEXT("Script");
}

FString FUnrealCSharpFunctionLibrary::GetBasePath()
{
	return FPaths::Combine(FPaths::ProjectDir(), GetBaseName());
}

FString FUnrealCSharpFunctionLibrary::GetUEProjectName()
{
	return TEXT("UE");
}

FString FUnrealCSharpFunctionLibrary::GetUEPath()
{
	return FPaths::Combine(GetBasePath(), GetUEProjectName());
}

FString FUnrealCSharpFunctionLibrary::GetUEProxyPath()
{
	return FPaths::Combine(GetUEPath(), TEXT("Proxy"));
}

FString FUnrealCSharpFunctionLibrary::GetGameProjectName()
{
	return TEXT("Game");
}

FString FUnrealCSharpFunctionLibrary::GetGamePath()
{
	return FPaths::Combine(GetBasePath(), GetGameProjectName());
}

FString FUnrealCSharpFunctionLibrary::GetGameProxyPath()
{
	return FPaths::Combine(GetGamePath(), TEXT("Proxy"));
}

FString FUnrealCSharpFunctionLibrary::GetBindingPath()
{
	return TEXT("Binding");
}

FString FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName()
{
	return ASSEMBLY_UTIL;
}

FString FUnrealCSharpFunctionLibrary::GetAssemblyUtilPath()
{
	return FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectPluginsDir() / PLUGIN_NAME, SCRIPT, GetAssemblyUtilProjectName()));
}

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

	const auto& ProjectModuleList = GetProjectModuleList();

	if (ProjectModuleList.Contains(Splits[0]) || (Splits[0] == TEXT("Script") && ProjectModuleList.Contains(Splits[1])))
	{
		return GetGameProxyPath();
	}
	else
	{
		return GetUEProxyPath();
	}
}

FString FUnrealCSharpFunctionLibrary::GetScriptPath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectContentDir(), SCRIPT));
}

FString FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()
{
	return FPaths::Combine(FPaths::ProjectIntermediateDir(), CODE_ANALYSIS);
}

TArray<FString> FUnrealCSharpFunctionLibrary::GetChangedDirectories()
{
	static auto GamePath = GetGamePath();

	TArray<FString> Directories;

	const auto& IgnoreDirectories = TArray<FString>{
		FPaths::Combine(GamePath, TEXT("Proxy")),
		FPaths::Combine(GamePath, TEXT("obj")),
		FPaths::Combine(GamePath, TEXT(".vs"))
	};

	IFileManager::Get().IterateDirectory(
		*GamePath, [&Directories, &IgnoreDirectories](const TCHAR* FilenameOrDirectory, const bool bIsDirectory)
		{
			if (bIsDirectory)
			{
				if (!IgnoreDirectories.Contains(FilenameOrDirectory))
				{
					Directories.Add(FilenameOrDirectory);
				}
			}

			return true;
		});

	return Directories;
}

FString FUnrealCSharpFunctionLibrary::Encode(const FString& InName, const bool bEncodeWideString)
{
	return FNameEncode::Encode(InName, bEncodeWideString);
}

const TArray<FString>& FUnrealCSharpFunctionLibrary::GetEngineModuleList()
{
	static TArray<FString> GameModuleList;

#if UE_ARRAY_IS_EMPTY
	if (GameModuleList.IsEmpty())
#else
	if (GameModuleList.Num() == 0)
#endif
	{
		static auto FilePath = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("UnrealCSharp_Modules.json"));

		FString JsonStr;

		if (FFileHelper::LoadFileToString(JsonStr, *FilePath))
		{
			const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

			TSharedPtr<FJsonObject> JsonObj;

			FJsonSerializer::Deserialize(JsonReader, JsonObj);

			JsonObj->TryGetStringArrayField(TEXT("EngineModules"), GameModuleList);

			JsonObj->TryGetStringArrayField(TEXT("EnginePlugins"), GameModuleList);
		}
	}

	return GameModuleList;
}

const TArray<FString>& FUnrealCSharpFunctionLibrary::GetProjectModuleList()
{
	static TArray<FString> GameModuleList;

#if UE_ARRAY_IS_EMPTY
	if (GameModuleList.IsEmpty())
#else
	if (GameModuleList.Num() == 0)
#endif
	{
		static auto FilePath = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("UnrealCSharp_Modules.json"));

		FString JsonStr;

		if (FFileHelper::LoadFileToString(JsonStr, *FilePath))
		{
			const auto& JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

			TSharedPtr<FJsonObject> JsonObj;

			FJsonSerializer::Deserialize(JsonReader, JsonObj);

			GameModuleList.Add(TEXT("Game"));

			JsonObj->TryGetStringArrayField(TEXT("ProjectModules"), GameModuleList);

			JsonObj->TryGetStringArrayField(TEXT("ProjectPlugins"), GameModuleList);
		}
	}

	return GameModuleList;
}
