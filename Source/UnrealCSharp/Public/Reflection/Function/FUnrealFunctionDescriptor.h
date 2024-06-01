#pragma once

#include "FFunctionDescriptor.h"
#include "mono/metadata/object.h"

class FUnrealFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FUnrealFunctionDescriptor(UFunction* InFunction);

public:
	MonoObject* ProcessEvent(UObject* InObject, MonoObject** OutValue, MonoArray* InValue) const;

	MonoObject* Invoke(UObject* InObject, MonoObject** OutValue, MonoArray* InValue) const;
};
