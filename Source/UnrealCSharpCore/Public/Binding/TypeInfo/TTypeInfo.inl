#pragma once

#include "FTypeInfo.h"
#include "TName.inl"
#include "TNameSpace.inl"

template <typename T>
struct TTypeInfo final : FTypeInfo
{
	virtual FString GetName() const override
	{
		return TName<std::decay_t<T>, std::decay_t<T>>::Get();
	}

	virtual const TArray<FString>& GetNameSpace() const override
	{
		static auto Instance = TNameSpace<std::decay_t<T>, std::decay_t<T>>::Get();

		return Instance;
	}

	virtual bool IsOut() const override
	{
		return std::is_reference_v<T> && !std::is_const_v<std::remove_reference_t<T>>;
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
		static TArray<FString> Instance;

		return Instance;
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
