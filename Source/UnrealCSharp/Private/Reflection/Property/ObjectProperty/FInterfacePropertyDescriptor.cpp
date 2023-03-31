#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TScriptInterface<IInterface>>(Src);

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

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TScriptInterface<IInterface>>(
			SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TScriptInterface<IInterface>>(Dest);

		InterfaceProperty->InitializeValue(Dest);

#if UE_INTERFACE_PROPERTY_SET_PROPERTY_VALUE
		InterfaceProperty->SetPropertyValue(Dest, SrcMulti.GetObject());
#else
		const auto Interface = static_cast<FScriptInterface*>(Dest);

		const auto Object = SrcMulti.GetObject();

		Interface->SetObject(Object);

		Interface->SetInterface(Object ? Object->GetInterfaceAddress(InterfaceProperty->InterfaceClass) : nullptr);
#endif

		Object_New(Dest);
	}
}

MonoObject* FInterfacePropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = InterfaceProperty->GetPropertyValuePtr(InAddress)->GetObject();

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(InterfaceProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TScriptInterface<IInterface>>(InAddress, Object, SrcObject);

	return Object;
}
