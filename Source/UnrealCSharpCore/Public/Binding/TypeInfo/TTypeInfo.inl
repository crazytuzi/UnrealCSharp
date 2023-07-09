#pragma once

#include "FTypeInfo.h"
#include "TName.inl"
#include "TNameSpace.inl"

template <typename T>
struct TTypeInfo final : FTypeInfo
{
	virtual FString GetName() const override
	{
		return TName<typename TDecay<T>::Type, typename TDecay<T>::Type>::Get();
	}

	virtual const TArray<FString>& GetNameSpace() const override
	{
		static auto Instance = TNameSpace<typename TDecay<T>::Type, typename TDecay<T>::Type>::Get();

		return Instance;
	}

	virtual bool IsOut() const override
	{
		return TAnd<TNot<TIsConst<T>>, TIsReferenceType<T>>::Value;
	}

	static FTypeInfo* Get()
	{
		static TTypeInfo Instance;

		return &Instance;
	}
};

template <>
struct TTypeInfo<void> final : FTypeInfo
{
	virtual FString GetName() const override
	{
		return {};
	}

	virtual const TArray<FString>& GetNameSpace() const override
	{
		return {};
	}

	virtual bool IsOut() const override
	{
		return false;
	}

	static FTypeInfo* Get()
	{
		return nullptr;
	}
};
