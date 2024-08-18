#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		const auto SrcObject = Property->GetObjectPropertyValue(Src);

		*Dest = FCSharpEnvironment::GetEnvironment().Bind(SrcObject);
	}
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

		const auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(
			SrcGarbageCollectionHandle);

		Property->InitializeValue(Dest);

		Property->SetObjectPropertyValue(Dest, SrcObject);
	}
}

bool FObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto ObjectA = Property->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetObject(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

		return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}
