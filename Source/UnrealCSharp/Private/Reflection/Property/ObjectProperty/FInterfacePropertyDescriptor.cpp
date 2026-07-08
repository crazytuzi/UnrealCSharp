#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TScriptInterface<IInterface>>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	const auto Interface = static_cast<FScriptInterface*>(Dest);

	const auto Object = SrcMulti->GetObject();

	Interface->SetObject(Object);

	Interface->SetInterface(Object ? Object->GetInterfaceAddress(Property->InterfaceClass) : nullptr);
}

bool FInterfacePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto InterfaceA = static_cast<FScriptInterface*>(const_cast<void*>(A));

	const auto InterfaceB = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return Property->Identical(InterfaceA, &InterfaceB, PortFlags);
}
