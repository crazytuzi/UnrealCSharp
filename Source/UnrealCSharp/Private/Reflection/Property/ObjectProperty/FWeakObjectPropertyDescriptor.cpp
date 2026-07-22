#include "Reflection/Property/ObjectProperty/FWeakObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TWeakObjectPtr<UObject>>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FParameter) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, false, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FWeakObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
}

bool FWeakObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ObjectA = Property->GetObjectPropertyValue(A);

	const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)))->Get();

	return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
}
