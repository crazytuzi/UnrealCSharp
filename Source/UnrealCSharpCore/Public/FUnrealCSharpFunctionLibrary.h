#pragma once

#include "CoreMinimal.h"

class UNREALCSHARPCORE_API FUnrealCSharpFunctionLibrary
{
public:
	static FString GetProxyPath();

	static FString GetGamePath();

	static FString GetModuleName(const UField* InField);

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetFullInterface(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetFullClass(const FDelegateProperty* InDelegateProperty);

	static FString GetClassNameSpace(const FDelegateProperty* InDelegateProperty);

	static FString GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetFileName(const UField* InField);

	static FString GetOldFileName(const UField* InField, const FString& OldName);
};
