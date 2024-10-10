#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto SrcObject = Property->GetObjectPropertyValue(Src);

	*Dest = FCSharpEnvironment::GetEnvironment().Bind(SrcObject);
}

void FObjectPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	const auto SrcObject = Property->GetObjectPropertyValue(Src);

	*Dest = FCSharpEnvironment::GetEnvironment().Bind(SrcObject);
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(
		SrcGarbageCollectionHandle);

	Property->InitializeValue(Dest);

	Property->SetObjectPropertyValue(Dest, SrcObject);
}

bool FObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ObjectA = Property->GetObjectPropertyValue(A);

	const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetObject(
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

	return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
}
