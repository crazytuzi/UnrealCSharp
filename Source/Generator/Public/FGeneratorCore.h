#pragma once

class FGeneratorCore
{
public:
	static FString GetBasePath();

	static FString GetModuleName(const UField* InField);

	static FString GetPathNameAttribute(const UField* InField);

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetFullClass(const UEnum* InEnum);

	static FString GetClassNameSpace(const UEnum* InStruct);

	static FString GetFullClass(const FDelegateProperty* InDelegateProperty);

	static FString GetClassNameSpace(const FDelegateProperty* InDelegateProperty);

	static FString GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty);

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

	static bool SaveStringToFile(const FString& FileName, const FString& String);
};
