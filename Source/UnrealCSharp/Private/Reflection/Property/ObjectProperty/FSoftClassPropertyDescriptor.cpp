#include "Reflection/Property/ObjectProperty/FSoftClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FSoftClassPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftClassProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TSoftClassPtr<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FSoftClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftClassProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TSoftClassPtr<UObject>>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSoftClassPtr<UObject>>(Dest);

		SoftClassProperty->InitializeValue(Dest);

		SoftClassProperty->SetObjectPropertyValue(Dest, SrcMulti.Get());

		Object_New(Dest);
	}
}

MonoObject* FSoftClassPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcClass = Cast<UClass>(SoftClassProperty->GetObjectPropertyValue(InAddress));

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(SoftClassProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSoftClassPtr<UObject>>(InAddress, Object, SrcClass);

	return Object;
}
