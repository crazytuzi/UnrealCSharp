#pragma once

template <typename T>
struct TIsTSoftObjectPtr
{
	enum { Value = false };
};

template <typename T>
struct TIsTSoftObjectPtr<TSoftObjectPtr<T>>
{
	enum { Value = true };
};
