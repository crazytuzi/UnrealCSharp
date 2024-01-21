#pragma once

#include "Binding/TypeInfo/TIsRef.inl"

template <typename... Args>
struct THasRef
{
	enum { Value = false };
};

template <typename T, typename... Args>
struct THasRef<T, Args...>
{
	enum { Value = TIsRef<T>::Value || THasRef<Args...>::Value };
};
