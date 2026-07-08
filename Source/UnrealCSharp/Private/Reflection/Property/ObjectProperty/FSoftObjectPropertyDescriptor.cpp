#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftObjectPtr<UObject>>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSoftObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	if (SrcMulti != nullptr)
	{
		Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FSoftObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ObjectA = Property->GetObjectPropertyValue(A);

	const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)))->Get();

	return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
}
