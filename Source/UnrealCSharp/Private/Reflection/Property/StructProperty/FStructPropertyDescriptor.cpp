#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FStructPropertyDescriptor::FStructPropertyDescriptor(FStructProperty* InProperty) :
	TCompoundPropertyDescriptor(InProperty)
{
	FCSharpEnvironment::GetEnvironment().Bind<false>(InProperty->Struct);
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetObject(Property->Struct, Src);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			Object = Class->NewObject(true);

			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(Property->Struct, Src, Object);
		}
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		Object = Class->NewObject(true);

		FCSharpEnvironment::GetEnvironment().AddStructReference<true>(Property->Struct, Src, Object);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FStructPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewRef(Src);
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
	if (const auto Struct = FCSharpEnvironment::GetEnvironment().GetStruct<>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->Identical(A, Struct, PortFlags);
	}

	return false;
}

IManagedHandle FStructPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetObject(Property->Struct, InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			Object = Class->NewObject(true);

			const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
				InAddress, Property);

			FCSharpEnvironment::GetEnvironment().AddStructReference(OwnerManagedHandle, Property->Struct,
			                                                        InAddress, Object);
		}
	}

	return Object;
}
