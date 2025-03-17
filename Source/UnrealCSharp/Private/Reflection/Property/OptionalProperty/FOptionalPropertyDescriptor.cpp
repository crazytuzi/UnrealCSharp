#include "Reflection/Property/OptionalProperty/FOptionalPropertyDescriptor.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Environment/FCSharpEnvironment.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto OptionalHelper = new FOptionalHelper(Property, Src, true, false);

	FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(Src, OptionalHelper, Object);

	*Dest = Object;
}

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetOptionalObject<FOptionalHelper>(Src);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto OptionalHelper = new FOptionalHelper(Property, Src, false, false);

		FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, true>(Src, OptionalHelper, Object);
	}

	*Dest = Object;
}

void FOptionalPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(
		SrcGarbageCollectionHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcOptional->GetData());
}
#endif
