#pragma once

#include "ClassMacro.h"

#if WITH_CORECLR
#define CORECLR_TYPE_NAME(A, B, Assembly) FString::Printf(TEXT("%s, %s"), *COMBINE_FULL_NAME(A, B), *Assembly)
#endif
