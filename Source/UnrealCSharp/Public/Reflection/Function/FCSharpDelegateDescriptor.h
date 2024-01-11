#pragma once

#include "FFunctionDescriptor.h"

class FCSharpDelegateDescriptor final : public FFunctionDescriptor
{
public:
	using FFunctionDescriptor::FFunctionDescriptor;

public:
	bool CallDelegate(MonoObject* InDelegate, void* InParams);

	MonoObject* ProcessDelegate(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue,
	                            MonoArray* InValue);

	MonoObject* ProcessMulticastDelegate(const FMulticastScriptDelegate* InMulticastScriptDelegate,
	                                     MonoObject** OutValue, MonoArray* InValue);
};
