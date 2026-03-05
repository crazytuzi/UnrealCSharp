#pragma once

#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"

template <class T>
auto FReflectionRegistry::GetClass() -> FClassReflection*
{
	return GetClass(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
}
