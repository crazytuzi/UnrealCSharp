#include "Reflection/Property/ObjectProperty/FLazyObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

FLazyObjectPropertyDescriptor::FLazyObjectPropertyDescriptor(FProperty* InProperty):
	FObjectPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(LazyObjectProperty);
}

void FLazyObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (LazyObjectProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FLazyObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (LazyObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(SrcMonoObject);

		LazyObjectProperty->InitializeValue(Dest);

		LazyObjectProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FLazyObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (LazyObjectProperty != nullptr)
	{
		const auto ObjectA = LazyObjectProperty->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(
			static_cast<MonoObject*>(const_cast<void*>(B)))->Get();

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
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TLazyObjectPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TLazyObjectPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
