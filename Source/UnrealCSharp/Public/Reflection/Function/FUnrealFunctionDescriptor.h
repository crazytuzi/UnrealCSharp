#pragma once

#include "FFunctionDescriptor.h"
#include "FFunctionParamBufferAllocator.h"
#include "mono/metadata/object.h"

class FUnrealFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FUnrealFunctionDescriptor(UFunction* InFunction);

public:
	MonoObject* CallUnreal(UObject* InObject, MonoObject** OutValue, MonoArray* InValue);

private:
	TSharedPtr<FFunctionParamBufferAllocator> BufferAllocator;
};
