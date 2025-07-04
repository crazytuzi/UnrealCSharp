#pragma once

#include "TIsPrimitive.inl"
#include "Template/TIsTEnumAsByte.inl"
#if UE_F_OPTIONAL_PROPERTY
#include "Template/TIsTOptional.inl"
#endif

template <typename T>
struct TIsRef
{
	static constexpr auto IsRef()
	{
		if constexpr (TIsPrimitive<T>::Value ||
			std::is_same_v<std::decay_t<T>, FName> ||
			std::is_same_v<std::decay_t<T>, FText> ||
			std::is_same_v<std::decay_t<T>, FString> ||
#if UE_F_UTF8_STR_PROPERTY
			std::is_same_v<std::decay_t<T>, FUtf8String> ||
#endif
#if UE_F_ANSI_STR_PROPERTY
			std::is_same_v<std::decay_t<T>, FAnsiString> ||
#endif
			std::is_pointer_v<std::decay_t<T>> ||
			TIsTArray<std::decay_t<T>>::Value ||
			TIsTSet<std::decay_t<T>>::Value ||
			TIsTMap<std::decay_t<T>>::Value
#if UE_F_OPTIONAL_PROPERTY
			|| TIsTOptional<std::decay_t<T>>::Value
#endif
		)
		{
			return std::is_reference_v<T> && !std::is_const_v<std::remove_reference_t<T>>;
		}
		else
		{
			return false;
		}
	}

	enum { Value = IsRef() };
};
