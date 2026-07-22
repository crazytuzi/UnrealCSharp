#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	const auto SrcObject = Property->GetObjectPropertyValue(Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = FCSharpEnvironment::GetEnvironment().Bind(SrcObject);
}

void FObjectPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	const auto SrcObject = Property->GetObjectPropertyValue(Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = FCSharpEnvironment::GetEnvironment().Bind(SrcObject);
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->SetObjectPropertyValue(Dest, SrcObject);
}

bool FObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ObjectA = Property->GetObjectPropertyValue(A);

	const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetObject(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
}
