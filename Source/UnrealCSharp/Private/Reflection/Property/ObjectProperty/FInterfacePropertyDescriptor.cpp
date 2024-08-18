#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src, bIsCopy);
	}
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
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
}

bool FInterfacePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto InterfaceA = static_cast<FScriptInterface*>(const_cast<void*>(A));

		const auto InterfaceB = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

		return Property->Identical(InterfaceA, &InterfaceB, PortFlags);
	}

	return false;
}

MonoObject* FInterfacePropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	if (bIsCopy)
	{
		const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, true>(
			Object, InAddress);

		return Object;
	}
	else
	{
		auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TScriptInterface<IInterface>>(InAddress);

		if (Object == nullptr)
		{
			Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, false>(
				Object, InAddress);
		}

		return Object;
	}
}
