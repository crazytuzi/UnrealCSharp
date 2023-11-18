#pragma once

#include "UEVersion.h"

#if UE_T_IS_T_ENUM_AS_BYTE
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
#endif
