#pragma once

template <typename T>
struct TIsTSoftClassPtr
{
	enum { Value = false };
};

template <typename T>
struct TIsTSoftClassPtr<TSoftClassPtr<T>>
{
	enum { Value = true };
};
