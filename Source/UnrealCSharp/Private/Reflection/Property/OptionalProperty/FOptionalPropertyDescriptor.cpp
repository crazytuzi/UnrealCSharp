#include "Reflection/Property/OptionalProperty/FOptionalPropertyDescriptor.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Environment/FCSharpEnvironment.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "UObject/PropertyOptional.h"

void FOptionalPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (OptionalProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FOptionalPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (OptionalProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(
			SrcGarbageCollectionHandle);

		OptionalProperty->InitializeValue(Dest);

		OptionalProperty->CopyCompleteValue(Dest, SrcOptional->GetData());
	}
}

MonoObject* FOptionalPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto OptionalHelper = new FOptionalHelper(OptionalProperty, InAddress);

	FCSharpEnvironment::GetEnvironment().AddOptionalReference(OptionalHelper, Object);

	return Object;
}
#endif
