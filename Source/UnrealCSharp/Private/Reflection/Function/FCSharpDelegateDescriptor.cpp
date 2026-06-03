#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FCSharpDelegateDescriptor::FCSharpDelegateDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPersistentBufferAllocator>(InFunction))
{
}

bool FCSharpDelegateDescriptor::CallDelegate(const UObject* InObject, const FMethodReflection* InMethod, void* InParams)
{
	return Invoke(
		InMethod,
		FCSharpEnvironment::GetEnvironment().GetObject(InObject),
		[this, InParams](const int32 InIndex) -> void*
		{
			return PropertyDescriptors[InIndex]->ContainerPtrToValuePtr<void>(InParams);
		},
		ReturnPropertyDescriptor != nullptr
			? ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams)
			: nullptr,
		[this, InParams](const FPropertyDescriptor* InPropertyDescriptor) -> void*
		{
			return InPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams);
		}
	);
}
