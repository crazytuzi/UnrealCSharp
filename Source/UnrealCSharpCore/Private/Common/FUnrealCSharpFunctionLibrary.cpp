﻿#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Misc/FileHelper.h"
#include "Common/NameEncode.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Setting/UnrealCSharpEditorSetting.h"
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
	                              InStruct->IsNative() &&
	                              !FDynamicClassGenerator::IsDynamicBlueprintGeneratedClass(InStruct)
		                              ? InStruct->GetPrefixCPP()
		                              : TEXT(""),
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

	if (InStruct->IsNative())
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

FString FUnrealCSharpFunctionLibrary::GetClassNameSpace(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return "";
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
	auto ModuleName = InAssetData.PackagePath.ToString();

	auto DirectoryName = FPaths::Combine(GetGenerationPath(ModuleName), ModuleName);

	return FPaths::Combine(DirectoryName, GetAssetName(InAssetData, InAssetName) + TEXT(".cs"));
}

FString FUnrealCSharpFunctionLibrary::GetOldFileName(const FAssetData& InAssetData, const FString& InOldObjectPath)
{
	return GetFileName(InAssetData, InOldObjectPath.Right(InOldObjectPath.Len() - InOldObjectPath.Find(TEXT(".")) - 1));
}
#endif

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

			for (const auto& Value : JsonObject->Values)
			{
				TArray<FString> Array;

				const auto& JsonValueArray = Value.Value->AsArray();

				for (auto Index = 0; Index < JsonValueArray.Num(); Index++)
				{
					if (FString Element; JsonValueArray[Index]->TryGetString(Element))
					{
						Array.Add(Element);
					}
				}

				Result.Add(Value.Key, Array);
			}
		}
	}

	return Result;
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
		return FString::Printf(TEXT("@%s"), *InName);
	}

	return FNameEncode::Encode(InName, bEncodeWideString);
}

const TArray<FString>& FUnrealCSharpFunctionLibrary::GetEngineModuleList()
{
	static TArray<FString> GameModuleList;

	if (GameModuleList.IsEmpty())
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

	if (GameModuleList.IsEmpty())
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
