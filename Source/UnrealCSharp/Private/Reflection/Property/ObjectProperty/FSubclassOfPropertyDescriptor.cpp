#include "Reflection/Property/ObjectProperty/FSubclassOfPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FParameter) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, false, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSubclassOfPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	if (SrcMulti != nullptr)
	{
		Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FSubclassOfPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ClassA = Cast<UClass>(Property->GetObjectPropertyValue(A));

	const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)))->Get();

	return Property->StaticIdentical(ClassA, ClassB, PortFlags);
}
