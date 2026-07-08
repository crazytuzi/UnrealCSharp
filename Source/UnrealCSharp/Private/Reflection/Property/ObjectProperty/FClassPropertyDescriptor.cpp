#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FClassPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto SrcClass = Cast<UClass>(Property->GetObjectPropertyValue(Src));

	*reinterpret_cast<IManagedHandle*>(Dest) = FCSharpEnvironment::GetEnvironment().Bind(SrcClass);
}

void FClassPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	const auto SrcClass = Cast<UClass>(Property->GetObjectPropertyValue(Src));

	*reinterpret_cast<IManagedHandle*>(Dest) = FCSharpEnvironment::GetEnvironment().Bind(SrcClass);
}

void FClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->SetObjectPropertyValue(Dest, SrcClass);
}

bool FClassPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ClassA = Cast<UClass>(Property->GetObjectPropertyValue(A));

	const auto ClassB = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return Property->StaticIdentical(ClassA, ClassB, PortFlags);
}
