#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, true>(
		Object, Src);

	*Dest = Object;
}

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TScriptInterface<IInterface>>(Src);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, false>(
			Object, Src);
	}

	*Dest = Object;
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
		SrcGarbageCollectionHandle);

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
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

	return Property->Identical(InterfaceA, &InterfaceB, PortFlags);
}
