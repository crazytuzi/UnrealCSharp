#include "FUnrealCSharpFunctionLibrary.h"
#include "Macro.h"
#include "Misc/FileHelper.h"

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

	return FString::Printf(TEXT(
		"%s%s"
	),
	                       InStruct->IsNative() ? InStruct->GetPrefixCPP() : TEXT(""),
	                       *InStruct->GetName());
}

FString FUnrealCSharpFunctionLibrary::GetFullInterface(const UStruct* InStruct)
{
	return FString::Printf(TEXT(
		"I%s"
	),
	                       *GetFullClass(InStruct).RightChop(1));
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

	const auto& GameModuleList = GetGameModuleList();

	if (GameModuleList.Contains(Splits[0]) || (Splits[0] == TEXT("Script") && GameModuleList.Contains(Splits[1])))
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

TArray<FString>& FUnrealCSharpFunctionLibrary::GetGameModuleList()
{
	static TArray<FString> GameModuleList;

	if(GameModuleList.IsEmpty())
	{
		auto FilePath = FPaths::Combine(FPaths::ProjectIntermediateDir(), TEXT("UnrealCSharp_GameModules.json"));

		FString JsonStr;
	
		bool bSuccess = FFileHelper::LoadFileToString(JsonStr, *FilePath);

		check(bSuccess);

		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

		TSharedPtr<FJsonObject> JsonObj;
		
		FJsonSerializer::Deserialize(JsonReader, JsonObj);
		
		JsonObj->TryGetStringArrayField(TEXT("GameModules"), GameModuleList);
	}
	
	return GameModuleList;
}
