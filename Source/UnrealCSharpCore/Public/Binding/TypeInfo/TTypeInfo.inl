#pragma once

#include "FTypeInfo.h"
#include "TIsRef.inl"
#include "TName.inl"
#include "TNameSpace.inl"
#include "TIsPrimitive.inl"

template <typename T, bool bIsStatic = false>
struct TTypeInfo final : FTypeInfo
{
	constexpr static auto IsReference()
	{
		return std::is_reference_v<T>;
	}

	virtual auto GetName() const -> FString override
	{
		return TName<T, T>::Get();
	}

	virtual auto GetNameSpace() const -> const TArray<FString>& override
	{
		static auto Instance = TNameSpace<T, T>::Get();

		return Instance;
	}

	virtual auto GetBufferSize() const -> int32 override
	{
		if constexpr (TIsPrimitive<T>::Value)
		{
			return sizeof(T);
		}
		else
		{
			return sizeof(void*);
		}
	}

	virtual auto IsRef() const -> bool override
	{
		return TIsRef<T>::Value;
	}

	virtual auto IsStatic() const -> bool override
	{
		return bIsStatic;
	}

	virtual auto IsPrimitive() const -> bool override
	{
		return TIsPrimitive<T>::Value;
	}

	static auto Get() -> FTypeInfo*
	{
		static TTypeInfo Instance;

		return &Instance;
	}
};

template <>
struct TTypeInfo<void> final : FTypeInfo
{
	virtual auto GetName() const -> FString override
	{
		return FString{};
	}

	virtual auto GetNameSpace() const -> const TArray<FString>& override
	{
		static TArray<FString> Instance;

		return Instance;
	}

	virtual auto IsRef() const -> bool override
	{
		return false;
	}

	virtual auto IsStatic() const -> bool override
	{
		return false;
	}

	virtual auto IsPrimitive() const -> bool override
	{
		return false;
	}

	static auto Get() -> FTypeInfo*
	{
		return nullptr;
	}
};
