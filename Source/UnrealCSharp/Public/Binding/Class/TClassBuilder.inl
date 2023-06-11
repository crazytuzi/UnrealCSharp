#pragma once

#include "FBindingClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <typename T>
class TClassBuilder final : public FBindingClassBuilder
{
public:
	explicit TClassBuilder(const FString& InImplementationNameSpace):
		FBindingClassBuilder(TClassName<T>::Get(), TTypeInfo<T, T>::Get(), InImplementationNameSpace)
	{
	}
};
