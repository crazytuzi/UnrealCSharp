#pragma once

class FGeneratorCore
{
public:
	static FString GetPathNameAttribute(const UField* InField);

	static FString GetPropertyType(FProperty* Property);

	static TSet<FString> GetPropertyTypeNameSpace(FProperty* Property);

	static FString GetGetAccessorType(FProperty* Property);

	static FString GetGetAccessorReturnParamName(FProperty* Property);

	static FString GetSetAccessorParamName(FProperty* Property);

	static bool IsPrimitiveProperty(FProperty* Property);

	static FString GetOutParamString(FProperty* Property, uint32 Index);

	static FString GetParamName(FProperty* Property);

	static FString GetReturnParamType(FProperty* Property);

	static int32 GetFunctionIndex(bool bHasReturn, bool bHasInput, bool bHasOutput);

	static bool SaveStringToFile(const FString& FileName, const FString& String);

	static bool IsSupported(FProperty* Property);

	static bool IsSupported(const UClass* InClass);

	static bool IsSupported(const UFunction* InFunction);

	static bool IsSupported(const UStruct* InStruct);

	static bool IsSupported(const UEnum* InEnum);

	static bool IsSupportedModule(const FString& InModule);

	static const TArray<FName>& GetSupportedAssetPath();

	static GENERATOR_API const TArray<FName>& GetSupportedAssetClassName();

	static GENERATOR_API void BeginGenerator();

	static GENERATOR_API void EndGenerator();

private:
	static TArray<FString> SupportedModule;

	static TArray<FName> SupportedAssetPath;

	static TArray<FString> SupportedAssetPathNameSpace;

	static TMap<TWeakObjectPtr<const UObject>, bool> SupportedMap;

	static TArray<FName> SupportedAssetClassName;
};
