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

	static FString GetModuleName(const UField* InField, const TFunction<void(FString& InModuleName)>& InGetModuleName);

	static FString GetModuleName(const FString& InModuleName);

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetFullInterface(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetFullClass(const UEnum* InEnum);

	static FString GetClassNameSpace(const UEnum* InEnum);

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

	static FString GetUEName();

#if WITH_EDITOR
	static FString GetUEDirectory();

	static FString GetUEProxyDirectory();

	static FString GetUEProjectPath();
#endif

	static FString GetGameName();

#if WITH_EDITOR
	static FString GetGameDirectory();

	static FString GetGameProxyDirectory();

	static FString GetGameProjectPath();

	static FString GetGameProjectPropsPath();
#endif

	static FString GetBindingDirectory();

	static FString GetPluginBaseDir();

	static FString GetPluginDirectory();

	static FString GetPluginScriptDirectory();

	static bool IsGameField(const UField* InField);

#if WITH_EDITOR
	static FString GetGenerationPath(const UField* InField);

	static FString GetGenerationPath(const FString& InScriptPath);
#endif

	static FString GetPublishDirectory();

	static FString GetFullPublishDirectory();

	static FString GetFullUEPublishPath();

	static FString GetFullGamePublishPath();

#if WITH_EDITOR
	static FString GetScriptDirectory();

	static FString GetFullScriptDirectory();

	static FString GetCodeAnalysisCSProjPath();

	static FString GetCodeAnalysisProjectPath();

	static FString GetCodeAnalysisPath();

	static FString GetSourceGeneratorPath();

	static FString GetWeaversPath();
#endif

	static class UAssemblyLoader* GetAssemblyLoader();

	static bool SaveStringToFile(const FString& InFileName, const FString& InString);

	static TMap<FString, TArray<FString>> LoadFileToArray(const FString& InFileName);

	static TMap<FString, FString> LoadFileToString(const FString& InFileName);

#if WITH_EDITOR
	static TArray<FString> GetChangedDirectories();
#endif

	static FString Encode(const FString& InName, bool bIsNative = true, bool bEncodeWideString = false);

	static FString Encode(const FProperty* InProperty);

	static FString Encode(const UFunction* InFunction);

	static const TArray<FString>& GetEngineModuleList();

	static const TArray<FString>& GetProjectModuleList();

#if WITH_EDITOR
	static bool IsSpecialClass(const UClass* InClass);

	static bool IsSpecialStruct(const UScriptStruct* InScriptStruct);

	static bool IsDynamicReInstanceField(const UField* InField);
#endif
};
