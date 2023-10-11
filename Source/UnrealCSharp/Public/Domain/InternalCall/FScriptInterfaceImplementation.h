#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FScriptInterfaceImplementation
{
public:
	static void ScriptInterface_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject,
	                                                   MonoString* InInterfaceName);

	static bool ScriptInterface_IdenticalImplementation(const FGarbageCollectionHandle InA,
	                                                    const FGarbageCollectionHandle InB);

	static void ScriptInterface_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void ScriptInterface_GetObjectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);
};
