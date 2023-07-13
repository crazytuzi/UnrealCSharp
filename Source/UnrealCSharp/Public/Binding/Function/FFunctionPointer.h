#pragma once

#include "mono/metadata/object.h"

#ifndef BINDING_FUNCTION_SIGNATURE
#define BINDING_FUNCTION_SIGNATURE MonoObject* InMonoObject, MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue
#endif

#ifndef BINDING_FUNCTION_PARAM
#define BINDING_FUNCTION_PARAM InMonoObject, ReturnValue, OutValue, InValue
#endif

struct FFunctionPointer
{
	explicit FFunctionPointer(void (*InFunction)(BINDING_FUNCTION_SIGNATURE))
	{
		Value.Function = InFunction;
	}

	union
	{
		void (*Function)(BINDING_FUNCTION_SIGNATURE);

		void* Pointer;
	} Value;
};
