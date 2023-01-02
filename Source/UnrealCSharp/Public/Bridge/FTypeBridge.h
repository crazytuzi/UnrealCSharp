#pragma once

#include "mono/metadata/object-forward.h"

class FTypeBridge
{
public:
	static EPropertyType GetPropertyType(MonoClass* InMonoClass);

	static MonoClass* GetMonoClass(const FProperty* InProperty);

	static FString GetFullClass(const UStruct* InStruct);

	static FString GetFullInterface(const UStruct* InStruct);

	static FString GetClassNameSpace(const UStruct* InStruct);

	static FString GetFullClass(const FDelegateProperty* InDelegateProperty);

	static FString GetClassNameSpace(const FDelegateProperty* InDelegateProperty);

	static FString GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty);

	static FString GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty);
};
