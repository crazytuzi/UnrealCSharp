#include "Reflection/Property/ObjectProperty/FSubclassOfPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			Object = Class->NewObject(true);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, false, true>(
				Class, Object, Src);
		}
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FParameter) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		Object = Class->NewObject(true);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, false, false>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		Object = Class->NewObject(true);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, true, false>(
			Class, Object, Src);
	}

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

	if (const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->StaticIdentical(ClassA, ClassB->Get(), PortFlags);
	}

	return false;
}
