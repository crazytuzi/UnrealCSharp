#pragma once
#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"

template <class T>
auto FReflectionRegistry::GetClassReflection() -> FClassReflection*
{
	return GetClassReflection(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
}
