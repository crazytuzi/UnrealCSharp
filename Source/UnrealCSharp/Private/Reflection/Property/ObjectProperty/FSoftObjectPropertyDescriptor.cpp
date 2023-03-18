#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TSoftObjectPtr<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FSoftObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TSoftObjectPtr<UObject>>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSoftObjectPtr<UObject>>(Dest);

		SoftObjectProperty->InitializeValue(Dest);

		SoftObjectProperty->SetObjectPropertyValue(Dest, SrcMulti.Get());

		Object_New(Dest);
	}
}

MonoObject* FSoftObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = SoftObjectProperty->GetObjectPropertyValue(InAddress);

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(SoftObjectProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSoftObjectPtr<UObject>>(InAddress, Object, SrcObject);

	return Object;
}
