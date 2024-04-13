﻿#pragma once

#include "FFunctionDescriptor.h"
#include "FFunctionParamBufferAllocator.h"
#include "mono/metadata/object.h"

class FCSharpDelegateDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FCSharpDelegateDescriptor(UFunction* InFunction);

public:
	bool CallDelegate(MonoObject* InDelegate, void* InParams);

	MonoObject* ProcessDelegate(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue,
	                            MonoArray* InValue);

	MonoObject* ProcessMulticastDelegate(const FMulticastScriptDelegate* InMulticastScriptDelegate,
	                                     MonoObject** OutValue, MonoArray* InValue);

private:
	TSharedPtr<FFunctionParamBufferAllocator> BufferAllocator;
};
