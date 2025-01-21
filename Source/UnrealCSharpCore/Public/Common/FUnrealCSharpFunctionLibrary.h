#pragma once

#include "CoreMinimal.h"
#include "UEVersion.h"

class UNREALCSHARPCORE_API FUnrealCSharpFunctionLibrary
{
public:
#if WITH_EDITOR
	static FString GetDotNet();
#endif

public:
	static FString GetModuleName(const UField* InField);

#if WITH_EDITOR
	static FString GetModuleRelativePath(const UField* InField);

	static FString GetModuleRelativePathMetaData(const UField* InField);
#endif

#if WITH_EDITOR
#if UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR
	static FString GetModuleName(const TObjectPtr<UFunction>& InSignatureFunction);
#else
	static FString GetModuleName(const UFunction* InSignatureFunction);
#endif
#endif

	static FString GetModuleName(const UPackage* InPackage);

	static FString GetModuleName(const FString& InName);

#if WITH_EDITOR
	static FString GetModuleRelativePath(const FDelegateProperty* InDelegateProperty);

	static FString GetModuleRelativePathMetaData(const FDelegateProperty* InDelegateProperty);

	static FString GetModuleRelativePath(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetModuleRelativePathMetaData(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static void ProcessModuleRelativePath(FString& OutModuleRelativePath);
#endif

#if WITH_EDITOR
#if UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR
	static FString GetOuterRelativePath(const TObjectPtr<UFunction>& InSignatureFunction);
#else
	static FString GetOuterRelativePath(const UFunction* InSignatureFunction);
#endif

	static FString GetOuterRelativePath(const FString& InRelativePath);

#if UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR
	static FString GetOuterName(const TObjectPtr<UFunction>& InSignatureFunction);
#else
	static FString GetOuterName(const UFunction* InSignatureFunction);
#endif

	static FString GetOuterName(const UPackage* InPackage);

	static FString GetOuterName(const UClass* InClass);

	static FString ProcessModuleRelativePathMetaData(const FString& InModuleRelativePathMetaData);
#endif

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetFullInterface(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetClassNameSpace(const UClass* InClass);

	static FString GetClassNameSpace(const UScriptStruct* InScriptStruct);

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

#if WITH_EDITOR
	static TArray<FString> GetCustomProjectsName();

	static TArray<FString> GetCustomProjectsDirectory();
#endif

#if WITH_EDITOR
	static bool IsRootPath(const FString& InPath);
#endif

	static bool EnableCallOverrideFunction();

	static FString GetOverrideFunctionNamePrefix();

	static FString GetOverrideFunctionNameSuffix();

	static FString GetOverrideFunctionName(const FString& InFunctionName);

	static FString GetOverrideFunctionName(const FName& InFunctionName);

	static FString GetBindingDirectory();

	static FString GetPluginBaseDir();

	static FString GetPluginDirectory();

	static FString GetPluginScriptDirectory();

#if WITH_EDITOR
	static FString GetPluginTemplateOverrideFileName(const UClass* InTemplateClass);

	static FString GetPluginTemplateDynamicFileName(const UClass* InTemplateClass);

	static FString GetPluginTemplateOverrideDirectory();

	static FString GetPluginTemplateDynamicDirectory();

	static FString GetPluginTemplateDirectory();
#endif

	static bool IsGameField(const UField* InField);

#if WITH_EDITOR
	static FString GetGenerationPath(const UField* InField);

	static FString GetGenerationPath(const FString& InScriptPath);
#endif

	static FString GetPublishDirectory();

	static FString GetFullPublishDirectory();

	static FString GetFullUEPublishPath();

	static FString GetFullGamePublishPath();

	static TArray<FString> GetFullCustomProjectsPublishPath();

	static TArray<FString> GetFullAssemblyPublishPath();

#if WITH_EDITOR
	static FString GetScriptDirectory();

	static FString GetFullScriptDirectory();

	static FString GetCodeAnalysisCSProjPath();

	static FString GetCodeAnalysisProjectPath();

	static FString GetCodeAnalysisPath();

	static FString GetSourceGeneratorPath();

	static FString GetWeaversPath();
#endif

#if WITH_EDITOR
	static bool IsGenerateFunctionComment();
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

	static bool IsSpecialEnum(const UEnum* InEnum);

	static bool IsDynamicReInstanceField(const UField* InField);
#endif

	static bool IsNativeFunction(const UClass* InClass, const FName& InFunctionName);

	template <typename T>
	static T* GetMutableDefaultSafe()
	{
		return !GExitPurge ? GetMutableDefault<T>() : nullptr;
	}
};
