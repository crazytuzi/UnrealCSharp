#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"

namespace
{
	struct FRegisterProperty
	{
		static void GetObjectPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, uint8* ReturnBuffer)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UObject, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress),
					                        ReturnBuffer);
				}
			}
		}

		static void SetObjectPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, uint8* InBuffer)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UObject, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Set(InBuffer,
					                        PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress));
				}
			}
		}

		static void GetStructPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, uint8* ReturnBuffer)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UScriptStruct, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress),
					                        ReturnBuffer);
				}
			}
		}

		static void SetStructPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, uint8* InBuffer)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UScriptStruct, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Set(InBuffer,
					                        PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress));
				}
			}
		}

		FRegisterProperty()
		{
			FClassBuilder(TEXT("FProperty"), NAMESPACE_LIBRARY, true)
				.Function("GetObjectProperty", GetObjectPropertyImplementation)
				.Function("SetObjectProperty", SetObjectPropertyImplementation)
				.Function("GetStructProperty", GetStructPropertyImplementation)
				.Function("SetStructProperty", SetStructPropertyImplementation);
		}
	};

	FRegisterProperty RegisterProperty;
}
