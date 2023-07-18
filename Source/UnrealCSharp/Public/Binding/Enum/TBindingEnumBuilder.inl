#pragma once

#include "Binding/Enum/FBindingEnum.h"
#include "Binding/TypeInfo/TTypeInfo.inl"

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
		FBindingEnum::GetEnum(TClassName<T>::Get(), TClassFullName<T>::Get(),
		                      TTypeInfo<T>::Get())->BindingEnumerator(InKey, static_cast<int64>(InValue));

		return *this;
	}

	void Register()
	{
	}
};
