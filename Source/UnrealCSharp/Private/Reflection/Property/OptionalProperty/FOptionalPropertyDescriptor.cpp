#include "Reflection/Property/OptionalProperty/FOptionalPropertyDescriptor.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Environment/FCSharpEnvironment.h"

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	const auto OptionalHelper = new FOptionalHelper(Property, Src, true, false);

	FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
		Src, OptionalHelper, Class, Object);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetOptionalObject<FOptionalHelper>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		const auto OptionalHelper = new FOptionalHelper(Property, Src, false, false);

		FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, true>(
			Src, OptionalHelper, Class, Object);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FOptionalPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcOptional->GetData());
}
#endif
