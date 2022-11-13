#pragma once

#include "FFunctionDescriptor.h"

class FCSharpDelegateDescriptor final : public FFunctionDescriptor
{
public:
	using FFunctionDescriptor::FFunctionDescriptor;

public:
	bool CallCSharp(MonoObject* InDelegateMonoObject, void* InParams);

	bool CallUnreal(const FScriptDelegate* InScriptDelegate, MonoObject** ReturnValue, MonoObject** OutValue,
	                MonoArray* InValue);
};
