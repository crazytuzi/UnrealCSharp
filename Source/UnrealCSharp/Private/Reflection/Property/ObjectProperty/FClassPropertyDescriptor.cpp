#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FClassPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ClassProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TSubclassOf<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ClassProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TSubclassOf<UObject>>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSubclassOf<UObject>>(Dest);

		ClassProperty->InitializeValue(Dest);
		
		ClassProperty->SetObjectPropertyValue(Dest, SrcMulti);

		Object_New(Dest);
	}
}

MonoObject* FClassPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcClass = Cast<UClass>(ClassProperty->GetObjectPropertyValue(InAddress));

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(ClassProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSubclassOf<UObject>>(InAddress, Object, SrcClass);

	return Object;
}
