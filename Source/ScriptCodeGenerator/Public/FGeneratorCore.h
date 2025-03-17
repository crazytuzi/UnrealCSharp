#pragma once

class FGeneratorCore
{
public:
	static FString GetPathNameAttribute(const UField* InField);

	static FString GetPropertyType(FProperty* Property);

	static TSet<FString> GetPropertyTypeNameSpace(FProperty* Property);

	static FString GetBufferCast(FProperty* Property);

	static int32 GetBufferSize(FProperty* Property);

	static FString GetTypeImplementation(FProperty* Property);

	static FString GetGetAccessorReturnParamName(FProperty* Property);

	static FString GetSetAccessorParamName(FProperty* Property);

	static bool IsPrimitiveProperty(FProperty* Property);

	static FString GetParamName(FProperty* Property);

	static FString GetFunctionPrefix(FProperty* Property);

	static int32 GetFunctionIndex(bool bHasReturn, bool bHasInput, bool bHasOutput, bool bIsNative, bool bIsNet);

	template <typename T>
	static auto GetFileName(const T* InField);

	static TArray<FString> GetOverrideFunctions(const FString& InNameSpace, const FString& InClass);

	static bool IsSkip(const UField* InField);

	static bool IsSupported(FProperty* Property);

	static bool IsSupported(const UClass* InClass);

	static bool IsSupported(const UFunction* InFunction);

	static bool IsSupported(const UScriptStruct* InScriptStruct);

	static bool IsSupported(const UEnum* InEnum);

	static bool IsSupportedModule(const FString& InModule);

	static const TArray<FName>& GetSupportedAssetPath();

	static SCRIPTCODEGENERATOR_API const TArray<FName>& GetSupportedAssetClassName();

	static SCRIPTCODEGENERATOR_API void BeginGenerator();

	static SCRIPTCODEGENERATOR_API void EndGenerator();

private:
	static TMap<FString, TArray<FString>> OverrideFunctionsMap;

	static bool bIsSkipGenerateEngineModules;

	static bool bIsGenerateAllModules;

	static TArray<FString> SupportedModule;

	static TArray<FName> SupportedAssetPath;

	static TArray<FString> SupportedAssetPathNameSpace;

	static TMap<TWeakObjectPtr<const UObject>, bool> SupportedMap;

	static TArray<FName> SupportedAssetClassName;
};

#include "FGeneratorCore.inl"
