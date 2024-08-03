#pragma once

#include "mono/metadata/details/object-types.h"

struct _MonoReflectionMethod
{
	MonoObject object;
	MonoMethod* method;
	MonoString* name;
	MonoReflectionType* reftype;
};
