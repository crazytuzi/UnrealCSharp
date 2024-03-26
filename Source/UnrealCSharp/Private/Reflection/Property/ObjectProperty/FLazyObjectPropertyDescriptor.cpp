#include "Reflection/Property/ObjectProperty/FLazyObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/PropertyMacro.h"

FLazyObjectPropertyDescriptor::FLazyObjectPropertyDescriptor(FProperty* InProperty):
	FObjectPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(LazyObjectProperty);

	Property = FMonoDomain::Class_Get_Property_From_Name(Class, PROPERTY_GARBAGE_COLLECTION_HANDLE);
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

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(
			FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(SrcMonoObject, Property));

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
			FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(static_cast<MonoObject*>(const_cast<void*>(B)), Property))->Get();

		return LazyObjectProperty->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}

MonoObject* FLazyObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TLazyObjectPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TLazyObjectPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
