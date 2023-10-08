#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FStructImplementation
{
public:
	static void Struct_StaticStructImplementation(MonoString* InStructName, MonoObject** OutValue);

	static void Struct_RegisterImplementation(MonoObject* InMonoObject, MonoString* InStructName);

	static bool Struct_IdenticalImplementation(const FGarbageCollectionHandle InScriptStruct,
	                                           const FGarbageCollectionHandle InA,
	                                           const FGarbageCollectionHandle InB);

	static void Struct_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);
};
