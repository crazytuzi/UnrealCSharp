#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/PropertyMacro.h"

FInterfacePropertyDescriptor::FInterfacePropertyDescriptor(FProperty* InProperty):
	FObjectPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(InterfaceProperty);

	Property = FMonoDomain::Class_Get_Property_From_Name(Class, PROPERTY_GARBAGE_COLLECTION_HANDLE);
}

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
			FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(SrcMonoObject, Property));

		InterfaceProperty->InitializeValue(Dest);

		const auto Interface = static_cast<FScriptInterface*>(Dest);

		const auto Object = SrcMulti->GetObject();

		Interface->SetObject(Object);

		Interface->SetInterface(Object ? Object->GetInterfaceAddress(InterfaceProperty->InterfaceClass) : nullptr);
	}
}

bool FInterfacePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto InterfaceA = static_cast<FScriptInterface*>(const_cast<void*>(A));

		const auto InterfaceB = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
			FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(static_cast<MonoObject*>(const_cast<void*>(B)), Property));

		return InterfaceProperty->Identical(InterfaceA, &InterfaceB, PortFlags);
	}

	return false;
}

MonoObject* FInterfacePropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TScriptInterface<IInterface>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>>(
			Object, InAddress, false);
	}

	return Object;
}
