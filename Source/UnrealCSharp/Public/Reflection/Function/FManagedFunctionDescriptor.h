#pragma once

#include "FFunctionDescriptor.h"

class FManagedFunctionDescriptor : public FFunctionDescriptor
{
public:
	using FFunctionDescriptor::FFunctionDescriptor;

protected:
	bool Invoke(const FMethodReflection* InMethod,
	            const IManagedHandle InManagedHandle,
	            const TFunctionRef<void*(int32)>& InPropertyAddress,
	            void* InReturnAddress,
	            const TFunctionRef<void*(const FPropertyDescriptor*)>& InOutPropertyAddress);
};
