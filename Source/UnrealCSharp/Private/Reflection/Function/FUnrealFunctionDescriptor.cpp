#include "Reflection/Function/FUnrealFunctionDescriptor.h"

FUnrealFunctionDescriptor::FUnrealFunctionDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InFunction))
{
}
