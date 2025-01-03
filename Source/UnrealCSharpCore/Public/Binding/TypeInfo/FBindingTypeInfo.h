#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"

struct FBindingTypeInfo
{
	explicit FBindingTypeInfo(FTypeInfo* InTypeInfo):
		TypeInfo(InTypeInfo)
	{
	}

	bool IsSet() const
	{
		return TypeInfo != nullptr;
	}

	FString GetName() const
	{
		return TypeInfo != nullptr ? TypeInfo->GetName() : FString();
	}

	const TArray<FString>& GetNameSpace() const
	{
		static TArray<FString> Instance;

		return TypeInfo != nullptr ? TypeInfo->GetNameSpace() : Instance;
	}

	int32 GetBufferSize() const
	{
		return TypeInfo != nullptr ? TypeInfo->GetBufferSize() : 0;
	}

	bool IsRef() const
	{
		return TypeInfo != nullptr ? TypeInfo->IsRef() : false;
	}

	bool IsStatic() const
	{
		return TypeInfo != nullptr ? TypeInfo->IsStatic() : false;
	}

	bool IsPrimitive() const
	{
		return TypeInfo != nullptr ? TypeInfo->IsPrimitive() : false;
	}

private:
	FTypeInfo* TypeInfo;
};
