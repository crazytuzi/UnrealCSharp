#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "FFunctionParamBufferAllocator.h"

class FFunctionDescriptor
{
public:
	explicit FFunctionDescriptor(UFunction* InFunction,
	                             const TSharedPtr<FFunctionParamBufferAllocator>& InBufferAllocator);

	virtual ~FFunctionDescriptor();

public:
	virtual void Initialize();

	virtual void Deinitialize();

public:
	FString GetName() const;

protected:
	TWeakObjectPtr<UFunction> Function;

	TArray<FPropertyDescriptor*> PropertyDescriptors;

	FPropertyDescriptor* ReturnPropertyDescriptor;

	TArray<uint32> ReferencePropertyIndexes;

	TArray<uint32> OutPropertyIndexes;

	TSharedPtr<FFunctionParamBufferAllocator> BufferAllocator;
};
