#pragma once

#include "FTypeInfo.h"
#include "TName.inl"
#include "TNameSpace.inl"

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
		if constexpr (std::is_same_v<std::decay_t<T>, bool> ||
			std::is_same_v<std::decay_t<T>, int8> ||
			std::is_same_v<std::decay_t<T>, int16> ||
			std::is_same_v<std::decay_t<T>, int32> ||
			std::is_same_v<std::decay_t<T>, int64> ||
			std::is_same_v<std::decay_t<T>, uint8> ||
			std::is_same_v<std::decay_t<T>, uint16> ||
			std::is_same_v<std::decay_t<T>, uint32> ||
			std::is_same_v<std::decay_t<T>, uint64> ||
			std::is_same_v<std::decay_t<T>, float> ||
			std::is_same_v<std::decay_t<T>, double> ||
			TIsEnum<std::decay_t<T>>::Value ||
			TIsEnumClass<std::decay_t<T>>::Value ||
			TIsTEnumAsByte<std::decay_t<T>>::Value ||
			std::is_same_v<std::decay_t<T>, FName> ||
			std::is_same_v<std::decay_t<T>, FText> ||
			std::is_same_v<std::decay_t<T>, FString> ||
			std::is_pointer_v<std::decay_t<T>> ||
			TIsTArray<std::decay_t<T>>::Value ||
			TIsTSet<std::decay_t<T>>::Value ||
			TIsTMap<std::decay_t<T>>::Value
		)
		{
			return std::is_reference_v<T> && !std::is_const_v<std::remove_reference_t<T>>;
		}
		else
		{
			return false;
		}
	}

	virtual bool IsStatic() const override
	{
		return bIsStatic;
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

	static FTypeInfo* Get()
	{
		return nullptr;
	}
};
