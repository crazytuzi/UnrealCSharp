#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"

namespace
{
	struct FRegisterProperty
	{
		static void GetObjectPropertyImplementation(const IManagedHandle InManagedHandle,
		                                            const uint32 InPropertyHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UObject, void*>(InManagedHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Get(
						PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress),
						RETURN_BUFFER);
				}
			}
		}

		static void SetObjectPropertyImplementation(const IManagedHandle InManagedHandle,
		                                            const uint32 InPropertyHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UObject, void*>(InManagedHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					const auto FoundValue = PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress);

					PropertyDescriptor->DestroyValue(FoundValue);

					PropertyDescriptor->Set(IN_BUFFER, FoundValue);
				}
			}
		}

		static void GetStructPropertyImplementation(const IManagedHandle InManagedHandle,
		                                            const uint32 InPropertyHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UScriptStruct, void*>(InManagedHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress),
					                        RETURN_BUFFER);
				}
			}
		}

		static void SetStructPropertyImplementation(const IManagedHandle InManagedHandle,
		                                            const uint32 InPropertyHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<
				UScriptStruct, void*>(InManagedHandle))
			{
				if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().
					GetOrAddPropertyDescriptor(InPropertyHash))
				{
					const auto FoundValue = PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress);

					PropertyDescriptor->DestroyValue(FoundValue);

					PropertyDescriptor->Set(IN_BUFFER, FoundValue);
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
