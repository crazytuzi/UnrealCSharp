#pragma once

#include "FTypeInfo.h"
#include "TName.inl"
#include "TNameSpace.inl"

template <typename T>
struct TTypeInfo final : FTypeInfo
{
	virtual FString GetName() const override
	{
		return TName<T, T>::Get();
	}

	virtual TArray<FString> GetNameSpace() const override
	{
		return TNameSpace<T, T>::Get();
	}

	static FTypeInfo* Get()
	{
		static TTypeInfo Instance;

		return &Instance;
	}
};
