#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FStructImplementation
{
public:
	static void Struct_StaticStructImplementation(MonoString* InStructName, MonoObject** OutValue);

	static void Struct_RegisterImplementation(MonoObject* InMonoObject, MonoString* InStructName);

	static void Struct_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);
};
