#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TScriptInterface<IInterface>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
			SrcMonoObject);

		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TScriptInterface<IInterface>>(Dest);

		InterfaceProperty->InitializeValue(Dest);

#if UE_INTERFACE_PROPERTY_SET_PROPERTY_VALUE
		InterfaceProperty->SetPropertyValue(Dest, SrcMulti->GetObject());
#else
		const auto Interface = static_cast<FScriptInterface*>(Dest);

		const auto Object = SrcMulti->GetObject();

		Interface->SetObject(Object);

		Interface->SetInterface(Object ? Object->GetInterfaceAddress(InterfaceProperty->InterfaceClass) : nullptr);
#endif

		Object_New(Dest);
	}
}

bool FInterfacePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto InterfaceA = static_cast<FScriptInterface*>(const_cast<void*>(A));

		const auto InterfaceB = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
			static_cast<MonoObject*>(const_cast<void*>(B)));

		return InterfaceProperty->Identical(InterfaceA, &InterfaceB, PortFlags);
	}

	return false;
}

MonoObject* FInterfacePropertyDescriptor::Object_New(void* InAddress) const
{
	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(InterfaceProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>>(
		Object, InAddress, false);

	return Object;
}
