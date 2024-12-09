#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"

namespace
{
	struct FRegisterProperty
	{
		static void GetObjectPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UObject, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress),
					                        RETURN_BUFFER);
				}
			}
		}

		static void SetObjectPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UObject, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Set(IN_BUFFER,
					                        PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress));
				}
			}
		}

		static void GetStructPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UScriptStruct, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress),
					                        RETURN_BUFFER);
				}
			}
		}

		static void SetStructPropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const uint32 InPropertyHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UScriptStruct, void*>(InGarbageCollectionHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Set(IN_BUFFER,
					                        PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress));
				}
			}
		}

		FRegisterProperty()
		{
			FClassBuilder(TEXT("FProperty"), NAMESPACE_LIBRARY)
				.Function("GetObjectProperty", GetObjectPropertyImplementation)
				.Function("SetObjectProperty", SetObjectPropertyImplementation)
				.Function("GetStructProperty", GetStructPropertyImplementation)
				.Function("SetStructProperty", SetStructPropertyImplementation);
		}
	};

	[[maybe_unused]] FRegisterProperty RegisterProperty;
}
