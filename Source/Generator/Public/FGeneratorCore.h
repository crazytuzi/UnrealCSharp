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

	static bool IsSafeProperty(FProperty* Property);

	static FString GetOutParamString(FProperty* Property, uint32 Index);

	static FString GetParamName(FProperty* Property);

	static FString GetReturnParamType(FProperty* Property);

	static FString GetReturnParamName(FProperty* Property);

	static FString GetName(FString InName);

	static bool SaveStringToFile(const FString& FileName, const FString& String);

	static FString GetPluginConfig();

	static FString GetProjectConfig();

	static bool IsSupported(FProperty* Property);

	static bool IsSupported(const UClass* InClass);

	static bool IsSupported(const UFunction* InFunction);

	static bool IsSupported(const UStruct* InStruct);

	static bool IsSupported(const UEnum* InEnum);

	static bool IsSupportedModule(const FString& InModule);

	static TArray<FName> GetAssetsPaths();

	static GENERATOR_API void BeginGenerator();

	static GENERATOR_API void EndGenerator();

private:
	static TArray<FString> SupportedModule;

	static TMap<TWeakObjectPtr<const UObject>, bool> SupportedMap;
};
