#include "Reflection/Property/OptionalProperty/FOptionalPropertyDescriptor.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Environment/FCSharpEnvironment.h"

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetOptionalObject<FOptionalHelper>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			Object = Class->NewObject();

			const auto OptionalHelper = new FOptionalHelper(Property, Src, false, false);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, true>(
				Src, OptionalHelper, Class, Object);
		}
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		Object = Class->NewObject();

		const auto OptionalHelper = new FOptionalHelper(Property, Src, true, false);

		FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
			Src, OptionalHelper, Class, Object);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FOptionalPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->CopyCompleteValue(Dest, SrcOptional->GetData());
	}
}

bool FOptionalPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
		*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->Identical(A, OptionalHelper->GetData(), PortFlags);
	}

	return false;
}
#endif
