#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"

#ifndef BINDING_CONSTRUCTOR_SIGNATURE
#define BINDING_CONSTRUCTOR_SIGNATURE MonoObject* InMonoObject, MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue
#endif

#ifndef BINDING_CONSTRUCTOR_PARAM
#define BINDING_CONSTRUCTOR_PARAM InMonoObject, ReturnValue, OutValue, InValue
#endif

#ifndef BINDING_FUNCTION_SIGNATURE
#define BINDING_FUNCTION_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue
#endif

#ifndef BINDING_FUNCTION_PARAM
#define BINDING_FUNCTION_PARAM InGarbageCollectionHandle, ReturnValue, OutValue, InValue
#endif

struct FFunctionPointer
{
	explicit FFunctionPointer(void (*InConstructor)(BINDING_CONSTRUCTOR_SIGNATURE))
	{
		Value.Constructor = InConstructor;
	}

	explicit FFunctionPointer(void (*InFunction)(BINDING_FUNCTION_SIGNATURE))
	{
		Value.Function = InFunction;
	}

	union
	{
		void (*Constructor)(BINDING_CONSTRUCTOR_SIGNATURE);

		void (*Function)(BINDING_FUNCTION_SIGNATURE);

		void* Pointer;
	} Value;
};
