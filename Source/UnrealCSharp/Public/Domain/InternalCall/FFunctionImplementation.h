#pragma once

#include "mono/metadata/object.h"

class FFunctionImplementation
{
public:
	static void CallReflectionMemberFunctionImplementation(const MonoObject& InMonoObject,
	                                                       const UTF16CHAR* InFunctionName, MonoObject** ReturnValue,
	                                                       MonoObject** OutValue, MonoArray* InValue);

	static void CallReflectionStaticFunctionImplementation(const UTF16CHAR* InClassName,
	                                                       const UTF16CHAR* InFunctionName, MonoObject** ReturnValue,
	                                                       MonoObject** OutValue, MonoArray* InValue);
};
