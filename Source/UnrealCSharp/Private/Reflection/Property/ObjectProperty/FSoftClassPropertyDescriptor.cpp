#include "Reflection/Property/ObjectProperty/FSoftClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSoftClassPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftClassPtr<UObject>>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSoftClassPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FParameter) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>, false, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSoftClassPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSoftClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
}

bool FSoftClassPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ClassA = Property->GetObjectPropertyValue(A);

	const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)))->Get();

	return Property->StaticIdentical(ClassA, ClassB, PortFlags);
}
