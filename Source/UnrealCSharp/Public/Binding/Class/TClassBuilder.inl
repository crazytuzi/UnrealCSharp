#pragma once
#include "Binding/Template/TClassName.inl"

template <typename T>
TClassBuilder<T>::TClassBuilder(const FString& InNameSpace):
	FBindingClassBuilder(TClassName<T>::Get(), InNameSpace)
{
}
