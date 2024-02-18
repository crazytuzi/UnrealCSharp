#pragma once

#define BINDING_CONSTRUCTOR_SIGNATURE MonoObject* InMonoObject, MonoObject** OutValue, MonoArray* InValue

#define BINDING_CONSTRUCTOR_PLACEHOLDER_SIGNATURE MonoObject* InMonoObject, void* Value0, void* Value1

#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM0 InMonoObject, nullptr, nullptr

#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM1 InMonoObject, static_cast<MonoObject**>(Value0), nullptr

#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM2 InMonoObject, nullptr, static_cast<MonoArray*>(Value0)

#define BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM3 InMonoObject, static_cast<MonoObject**>(Value0), static_cast<MonoArray*>(Value1)

#define BINDING_DESTRUCTOR_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle

#define BINDING_DESTRUCTOR_PARAM InGarbageCollectionHandle

#define BINDING_FUNCTION_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue, MonoArray* InValue

#define BINDING_FUNCTION_PLACEHOLDER_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, void* Value0, void* Value1

#define BINDING_FUNCTION_PLACEHOLDER_PARAM0 InGarbageCollectionHandle, nullptr, nullptr

#define BINDING_FUNCTION_PLACEHOLDER_PARAM1 InGarbageCollectionHandle, static_cast<MonoObject**>(Value0), nullptr

#define BINDING_FUNCTION_PLACEHOLDER_PARAM2 InGarbageCollectionHandle, nullptr, static_cast<MonoArray*>(Value0)

#define BINDING_FUNCTION_PLACEHOLDER_PARAM3 InGarbageCollectionHandle, static_cast<MonoObject**>(Value0), static_cast<MonoArray*>(Value1)

#define BINDING_SUBSCRIPT_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, MonoArray* InValue

#define BINDING_SUBSCRIPT_PARAM InGarbageCollectionHandle, InValue
