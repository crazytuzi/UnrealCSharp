#pragma once

#include "FFunctionDescriptor.h"

class FCSharpDelegateDescriptor final : public FFunctionDescriptor
{
public:
	using FFunctionDescriptor::FFunctionDescriptor;

public:
	bool CallDelegate(MonoObject* InDelegate, void* InParams);

	bool ProcessDelegate(const FScriptDelegate* InScriptDelegate, MonoObject** ReturnValue, MonoObject** OutValue,
	                     MonoArray* InValue);

	bool ProcessMulticastDelegate(const FMulticastScriptDelegate* InMulticastScriptDelegate, MonoObject** OutValue,
	                              MonoArray* InValue);
};
