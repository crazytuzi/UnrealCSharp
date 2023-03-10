#pragma once

#include "mono/metadata/object.h"

class FScriptInterfaceImplementation
{
public:
	static void ScriptInterface_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static void ScriptInterface_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void ScriptInterface_GetObjectImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
