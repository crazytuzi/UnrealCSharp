#include "Reflection/Property/ObjectProperty/FWeakObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FWeakObjectPropertyDescriptor::FWeakObjectPropertyDescriptor(FProperty* InProperty):
	FCompoundPropertyDescriptor(InProperty)
{
}

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (WeakObjectProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FWeakObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (WeakObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(
			MonoObject2GarbageCollectionHandle(SrcMonoObject));

		WeakObjectProperty->InitializeValue(Dest);

		WeakObjectProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FWeakObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (WeakObjectProperty != nullptr)
	{
		const auto ObjectA = WeakObjectProperty->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(
			MonoObject2GarbageCollectionHandle(static_cast<MonoObject*>(const_cast<void*>(B))))->Get();

		return WeakObjectProperty->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}

MonoObject* FWeakObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TWeakObjectPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
