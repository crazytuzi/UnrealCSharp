#pragma once

template <typename T>
struct TIsTWeakObjectPtr
{
	enum { Value = false };
};

template <typename T>
struct TIsTWeakObjectPtr<TWeakObjectPtr<T>>
{
	enum { Value = true };
};
