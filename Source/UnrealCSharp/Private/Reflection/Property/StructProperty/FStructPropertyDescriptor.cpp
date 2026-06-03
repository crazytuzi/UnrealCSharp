#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedTypes.h"

FStructPropertyDescriptor::FStructPropertyDescriptor(FStructProperty* InProperty) :
	TCompoundPropertyDescriptor(InProperty)
{
	FCSharpEnvironment::GetEnvironment().Bind<false>(InProperty->Struct);
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStructReference<true>(Property->Struct, Src,
	                                                              MANAGED_HANDLE_FROM_OBJECT(Object));
	*reinterpret_cast<IManagedObject*>(Dest) = IManagedHandleToIManagedObject(Object);
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStructReference<false>(Property->Struct, Src,
	                                                               MANAGED_HANDLE_FROM_OBJECT(Object));
	*reinterpret_cast<IManagedObject*>(Dest) = IManagedHandleToIManagedObject(Object);
}

void FStructPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<IManagedObject*>(Dest) = NewRef(Src);
}

void FStructPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct<>(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->CopySingleValue(Dest, SrcStruct);
	}
}

bool FStructPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto StructA = Property->ContainerPtrToValuePtr<void>(A);

	const auto StructB = FCSharpEnvironment::GetEnvironment().GetStruct<>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return Property->Identical(StructA, StructB, PortFlags);
}

IManagedObject FStructPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetObject(Property->Struct, InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddStructReference(OwnerManagedHandle, Property->Struct,
		                                                        InAddress, MANAGED_HANDLE_FROM_OBJECT(Object));
	}

	return IManagedHandleToIManagedObject(Object);
}
