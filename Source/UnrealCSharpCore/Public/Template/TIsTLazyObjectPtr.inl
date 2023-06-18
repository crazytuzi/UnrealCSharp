#pragma once

template <typename T>
struct TIsTLazyObjectPtr
{
	enum { Value = false };
};

template <typename T>
struct TIsTLazyObjectPtr<TLazyObjectPtr<T>>
{
	enum { Value = true };
};
