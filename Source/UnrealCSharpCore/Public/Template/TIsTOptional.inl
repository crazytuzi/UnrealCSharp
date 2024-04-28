#pragma once

#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TIsTOptional
{
	enum { Value = TIsTOptional_V<T> };
};
#endif
