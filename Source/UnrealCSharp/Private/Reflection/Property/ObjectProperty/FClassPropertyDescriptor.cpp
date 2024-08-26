#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FClassPropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		const auto SrcClass = Cast<UClass>(Property->GetObjectPropertyValue(Src));

		*Dest = FCSharpEnvironment::GetEnvironment().Bind(SrcClass);
	}
}

void FClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

		const auto SrcClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(
			SrcGarbageCollectionHandle);

		Property->InitializeValue(Dest);

		Property->SetObjectPropertyValue(Dest, SrcClass);
	}
}

bool FClassPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto ClassA = Cast<UClass>(Property->GetObjectPropertyValue(A));

		const auto ClassB = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

		return Property->StaticIdentical(ClassA, ClassB, PortFlags);
	}

	return false;
}
