#pragma once

#ifndef BINDING_CONSTRUCTOR_SIGNATURE
#define BINDING_CONSTRUCTOR_SIGNATURE MonoObject* InMonoObject, MonoObject** OutValue, MonoArray* InValue
#endif

#ifndef BINDING_CONSTRUCTOR_PLACEHOLDER_SIGNATURE
#define BINDING_CONSTRUCTOR_PLACEHOLDER_SIGNATURE MonoObject* InMonoObject, void* Value0, void* Value1
#endif

#ifndef BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM0
#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM0 InMonoObject, nullptr, nullptr
#endif

#ifndef BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM1
#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM1 InMonoObject, static_cast<MonoObject**>(Value0), nullptr
#endif

#ifndef BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM2
#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM2 InMonoObject, nullptr, static_cast<MonoArray*>(Value0)
#endif

#ifndef BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM3
#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM3 InMonoObject, static_cast<MonoObject**>(Value0), static_cast<MonoArray*>(Value1)
#endif

#ifndef BINDING_DESTRUCTOR_SIGNATURE
#define BINDING_DESTRUCTOR_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle
#endif

#ifndef BINDING_DESTRUCTOR_PARAM
#define BINDING_DESTRUCTOR_PARAM InGarbageCollectionHandle
#endif

#ifndef BINDING_FUNCTION_SIGNATURE
#define BINDING_FUNCTION_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue, MonoArray* InValue
#endif

#ifndef BINDING_FUNCTION_PLACEHOLDER_SIGNATURE
#define BINDING_FUNCTION_PLACEHOLDER_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, void* Value0, void* Value1
#endif

#ifndef BINDING_FUNCTION_PLACEHOLDER_PARAM0
#define BINDING_FUNCTION_PLACEHOLDER_PARAM0 InGarbageCollectionHandle, nullptr, nullptr
#endif

#ifndef BINDING_FUNCTION_PLACEHOLDER_PARAM1
#define BINDING_FUNCTION_PLACEHOLDER_PARAM1 InGarbageCollectionHandle, static_cast<MonoObject**>(Value0), nullptr
#endif

#ifndef BINDING_FUNCTION_PLACEHOLDER_PARAM2
#define BINDING_FUNCTION_PLACEHOLDER_PARAM2 InGarbageCollectionHandle, nullptr, static_cast<MonoArray*>(Value0)
#endif

#ifndef BINDING_FUNCTION_PLACEHOLDER_PARAM3
#define BINDING_FUNCTION_PLACEHOLDER_PARAM3 InGarbageCollectionHandle, static_cast<MonoObject**>(Value0), static_cast<MonoArray*>(Value1)
#endif

#ifndef BINDING_SUBSCRIPT_SIGNATURE
#define BINDING_SUBSCRIPT_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, MonoArray* InValue
#endif

#ifndef BINDING_SUBSCRIPT_PARAM
#define BINDING_SUBSCRIPT_PARAM InGarbageCollectionHandle, InValue
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
