#include "Reflection/Property/ObjectProperty/FLazyObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

void FLazyObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (LazyObjectProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TLazyObjectPtr<UObject>>(Src);

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

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(SrcMonoObject);

		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TLazyObjectPtr<UObject>>(Dest);

		LazyObjectProperty->InitializeValue(Dest);

		LazyObjectProperty->SetObjectPropertyValue(Dest, SrcMulti.Get());

		Object_New(Dest);
	}
}

bool FLazyObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (LazyObjectProperty != nullptr)
	{
		const auto ObjectA = LazyObjectProperty->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(
			static_cast<MonoObject*>(const_cast<void*>(B))).Get();

#if UE_OBJECT_PROPERTY_STATIC_IDENTICAL
		return LazyObjectProperty->StaticIdentical(ObjectA, ObjectB, PortFlags);
#else
		return ObjectA == ObjectB;
#endif
	}

	return false;
}

MonoObject* FLazyObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = LazyObjectProperty->GetObjectPropertyValue(InAddress);

	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(LazyObjectProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TLazyObjectPtr<UObject>>(InAddress, Object, SrcObject);

	return Object;
}
