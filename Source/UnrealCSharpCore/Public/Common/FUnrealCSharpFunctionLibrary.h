#pragma once

#include "CoreMinimal.h"

class UNREALCSHARPCORE_API FUnrealCSharpFunctionLibrary
{
public:
#if WITH_EDITOR
	static FString GetDotNet();
#endif

public:
	static FString GetModuleName(const UField* InField);

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetFullInterface(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetFullClass(const UEnum* InEnum);

	static FString GetClassNameSpace(const UEnum* InStruct);

	static FString GetFullClass(const FDelegateProperty* InDelegateProperty);

	static FString GetClassNameSpace(const FDelegateProperty* InDelegateProperty);

	static FString GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty);

#if WITH_EDITOR
	static FString GetSuffixName(const FAssetData& InAssetData);

	static FString GetAssetName(const FAssetData& InAssetData, const FString& InAssetName);

	static FString GetObjectPathName(const FAssetData& InAssetData, const FString& InObjectPathName);

	static FString GetAssetClass(const FAssetData& InAssetData, const FString& InClass);

	static FString GetFileName(const FAssetData& InAssetData);

	static FString GetFileName(const FAssetData& InAssetData, const FString& InAssetName);

	static FString GetOldFileName(const FAssetData& InAssetData, const FString& InOldObjectPath);
#endif

	static FString GetBaseName();

	static FString GetBasePath();

	static FString GetUEProjectName();

	static FString GetUEPath();

	static FString GetUEProxyPath();

	static FString GetGameProjectName();

	static FString GetGamePath();

	static FString GetGameProxyPath();

	static FString GetBindingPath();

	static FString GetAssemblyUtilProjectName();

	static FString GetAssemblyUtilPath();

	static FString GetGenerationPath(const UField* InField);

	static FString GetGenerationPath(const FString& InScriptPath);

	static FString GetScriptPath();

	static FString GetCodeAnalysisPath();

	static TArray<FString> GetChangedDirectories();

	static FString Encode(const FString& InName, bool bEncodeWideString = false);

	static const TArray<FString>& GetEngineModuleList();

	static const TArray<FString>& GetProjectModuleList();
};
