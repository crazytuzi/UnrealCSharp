#include "Reflection/Property/ObjectProperty/FWeakObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (WeakObjectProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TWeakObjectPtr<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FWeakObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (WeakObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TWeakObjectPtr<UObject>>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TWeakObjectPtr<UObject>>(Dest);

		WeakObjectProperty->InitializeValue(Dest);
		
		WeakObjectProperty->SetObjectPropertyValue(Dest, SrcMulti.Get());

		Object_New(Dest);
	}
}

MonoObject* FWeakObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = WeakObjectProperty->GetObjectPropertyValue(InAddress);

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(WeakObjectProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TWeakObjectPtr<UObject>>(InAddress, Object, SrcObject);

	return Object;
}
