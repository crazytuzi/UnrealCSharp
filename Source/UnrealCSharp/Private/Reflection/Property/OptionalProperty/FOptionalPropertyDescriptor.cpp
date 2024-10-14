#include "Reflection/Property/OptionalProperty/FOptionalPropertyDescriptor.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Environment/FCSharpEnvironment.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*Dest = NewWeakRef(Src, true);
}

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*Dest = NewWeakRef(Src, false);
}

void FOptionalPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(
		SrcGarbageCollectionHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcOptional->GetData());
}

MonoObject* FOptionalPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto OptionalHelper = new FOptionalHelper(Property, InAddress,
	                                                bIsCopy, false);

	FCSharpEnvironment::GetEnvironment().AddOptionalReference(OptionalHelper, Object);

	return Object;
}
#endif
