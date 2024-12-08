#pragma once

#define BINDING_CONSTRUCTOR_SIGNATURE MonoObject* InMonoObject, uint8* InBuffer, uint8* OutBuffer

#define BINDING_CONSTRUCTOR_PARAM InMonoObject, InBuffer, OutBuffer

#define BINDING_DESTRUCTOR_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle

#define BINDING_DESTRUCTOR_PARAM InGarbageCollectionHandle

#define BINDING_FUNCTION_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, uint8* InBuffer, uint8* OutBuffer, uint8* ReturnBuffer

#define BINDING_FUNCTION_PARAM InGarbageCollectionHandle, InBuffer, OutBuffer, ReturnBuffer

#define BINDING_SUBSCRIPT_GET_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, uint8* InBuffer, uint8* ReturnBuffer

#define BINDING_SUBSCRIPT_GET_PARAM InGarbageCollectionHandle, InBuffer, ReturnBuffer

#define BINDING_SUBSCRIPT_SET_SIGNATURE const FGarbageCollectionHandle InGarbageCollectionHandle, uint8* InBuffer

#define BINDING_SUBSCRIPT_SET_PARAM InGarbageCollectionHandle, InBuffer
