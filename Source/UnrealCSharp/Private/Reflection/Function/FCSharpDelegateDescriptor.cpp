#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/MonoMacro.h"

FCSharpDelegateDescriptor::FCSharpDelegateDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPersistentBufferAllocator>(InFunction))
{
}

bool FCSharpDelegateDescriptor::CallDelegate(const UObject* InObject, MonoMethod* InMethod, void* InParams)
{
	const auto CSharpParams = FCSharpEnvironment::GetEnvironment().GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment().GetDomain()->Get_Object_Class(), PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		if (const auto PropertyDescriptor = PropertyDescriptors[Index])
		{
			void* Object = nullptr;

			PropertyDescriptor->Get<std::false_type>(PropertyDescriptor->ContainerPtrToValuePtr<void>(InParams),
			                                         &Object);

			ARRAY_SET(CSharpParams, MonoObject*, Index, static_cast<MonoObject*>(Object));
		}
	}

	if (const auto ReturnValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke_Array(
			InMethod, FCSharpEnvironment::GetEnvironment().GetObject(InObject), CSharpParams);
		ReturnValue != nullptr && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
				ReturnValue))
			{
				ReturnPropertyDescriptor->Set(UnBoxResultValue,
				                              ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
			}
		}
		else
		{
			ReturnPropertyDescriptor->Set(FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(ReturnValue),
			                              ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
		}
	}

	if (!OutPropertyIndexes.IsEmpty())
	{
		for (const auto& Index : OutPropertyIndexes)
		{
			if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
			{
				if (OutPropertyDescriptor->IsPrimitiveProperty())
				{
					if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment().GetDomain()->
						Object_Unbox(ARRAY_GET(CSharpParams, MonoObject*, Index)))
					{
						OutPropertyDescriptor->Set(UnBoxResultValue,
						                           OutPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
					}
				}
				else
				{
					OutPropertyDescriptor->Set(
						FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(
							ARRAY_GET(CSharpParams, MonoObject*, Index)),
						OutPropertyDescriptor->ContainerPtrToValuePtr<void>(InParams));
				}
			}
		}
	}

	return true;
}
