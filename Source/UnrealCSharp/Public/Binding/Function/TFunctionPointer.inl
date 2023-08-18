#pragma once

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

template <typename T>
struct TFunctionPointer
{
	explicit TFunctionPointer(const T& InFunction)
	{
		Value.Function = InFunction;
	}

	union
	{
		T Function;

		void* Pointer;
	} Value;
};
