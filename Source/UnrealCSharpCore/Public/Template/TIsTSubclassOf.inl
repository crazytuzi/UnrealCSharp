#pragma once

#include "UEVersion.h"

#if UE_T_IS_T_SUB_CLASS_OF
template <typename T>
struct TIsTSubclassOf
{
	enum { Value = false };
};

template <typename T>
struct TIsTSubclassOf<TSubclassOf<T>>
{
	enum { Value = true };
};
#endif
