#include "Reflection/Property/ObjectProperty/FLazyObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FLazyObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (LazyObjectProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TLazyObjectPtr<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FLazyObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (LazyObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TLazyObjectPtr<UObject>>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TLazyObjectPtr<UObject>>(Dest);

		LazyObjectProperty->InitializeValue(Dest);
		
		LazyObjectProperty->SetObjectPropertyValue(Dest, SrcMulti.Get());

		Object_New(Dest);
	}
}

MonoObject* FLazyObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = LazyObjectProperty->GetObjectPropertyValue(InAddress);

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(LazyObjectProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TLazyObjectPtr<UObject>>(InAddress, Object, SrcObject);

	return Object;
}
