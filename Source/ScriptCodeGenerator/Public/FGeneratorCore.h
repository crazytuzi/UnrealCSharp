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

	static const FString& GetGeneratorHeaderComment();

	static void AddGeneratorFile(const FString& InFile);

	static bool IsSkip(const UField* InField);

	static bool IsSupported(FProperty* Property);

	static bool IsSupported(const UPackage* InPackage);

	static bool IsSupported(const UClass* InClass);

	static bool IsSupported(const UFunction* InFunction);

	static bool IsSupported(const UScriptStruct* InScriptStruct);

	static bool IsSupported(const UEnum* InEnum);

	static SCRIPTCODEGENERATOR_API bool IsSupported(const FAssetData& InAssetData);

	static SCRIPTCODEGENERATOR_API const TArray<FName>& GetSupportedAssetClassName();

	static SCRIPTCODEGENERATOR_API void BeginGenerator(bool bIsFull = true);

	static SCRIPTCODEGENERATOR_API void EndGenerator(bool bIsFull = true);

private:
	static void DeleteRemainGeneratorFiles();

private:
	static TMap<FString, TArray<FString>> OverrideFunctionsMap;

	static bool bIsSkipGenerateEngineModules;

	static bool bIsGenerateAllModules;

	static TArray<FString> SupportedModule;

	static TArray<FString> SupportedAssetPath;

	static TMap<TWeakObjectPtr<const UObject>, bool> SupportedMap;

	static TArray<FName> SupportedAssetClassName;

	static FString GeneratorHeaderComment;

	static TSet<FString> GeneratorFiles;
};

#include "FGeneratorCore.inl"
