#pragma once

#include "FTypeInfo.h"
#include "TIsRef.inl"
#include "TName.inl"
#include "TNameSpace.inl"
#include "TIsPrimitive.inl"

template <typename T, bool bIsStatic = false>
struct TTypeInfo final : FTypeInfo
{
	constexpr static bool IsReference()
	{
		return std::is_reference_v<T>;
	}

	virtual FString GetName() const override
	{
		return TName<T, T>::Get();
	}

	virtual const TArray<FString>& GetNameSpace() const override
	{
		static auto Instance = TNameSpace<T, T>::Get();

		return Instance;
	}

	virtual bool IsRef() const override
	{
		return TIsRef<T>::Value;
	}

	virtual bool IsStatic() const override
	{
		return bIsStatic;
	}

	virtual bool IsPrimitive() const override
	{
		return TIsPrimitive<T>::Value;
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

	virtual bool IsRef() const override
	{
		return false;
	}

	virtual bool IsStatic() const override
	{
		return false;
	}

	virtual bool IsPrimitive() const override
	{
		return false;
	}

	static FTypeInfo* Get()
	{
		return nullptr;
	}
};
