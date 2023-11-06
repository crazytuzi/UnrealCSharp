#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"

struct FBindingTypeInfo
{
	FBindingTypeInfo() = default;

	explicit FBindingTypeInfo(FTypeInfo* InInfo): Info(InInfo)
	{
	}

	FString GetName() const
	{
		return Info != nullptr ? Info->GetName() : FString();
	}

	const TArray<FString>& GetNameSpace() const
	{
		static TArray<FString> Instance;

		return Info != nullptr ? Info->GetNameSpace() : Instance;
	}

	bool IsRef() const
	{
		return Info != nullptr ? Info->IsRef() : false;
	}

private:
	FTypeInfo* Info;
};
