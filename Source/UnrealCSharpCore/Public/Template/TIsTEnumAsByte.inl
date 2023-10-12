#pragma once

template <typename T>
struct TIsTEnumAsByte
{
	enum { Value = false };
};

template <typename T>
struct TIsTEnumAsByte<TEnumAsByte<T>>
{
	enum { Value = true };
};
