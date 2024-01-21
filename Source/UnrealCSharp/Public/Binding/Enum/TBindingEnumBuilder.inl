#pragma once

#include "Binding/Enum/FBindingEnum.h"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Binding/Template/TClassName.inl"

template <typename T>
class TBindingEnumBuilder
{
public:
	TBindingEnumBuilder()
	{
	}

public:
	template <typename Type>
	TBindingEnumBuilder& Enumerator(const FString& InKey, const Type InValue)
	{
		FBindingEnum::GetEnum(TClassName<T>::Get(),
		                      TName<std::underlying_type_t<Type>, std::underlying_type_t<Type>>::Get(),
		                      TTypeInfo<T>::Get())->
			BindingEnumerator(InKey, static_cast<std::underlying_type_t<Type>>(InValue));

		return *this;
	}

	void Register()
	{
	}
};
