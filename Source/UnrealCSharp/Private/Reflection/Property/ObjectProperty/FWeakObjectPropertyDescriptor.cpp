#include "Reflection/Property/ObjectProperty/FWeakObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src, bIsCopy);
	}
}

void FWeakObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(
			SrcGarbageCollectionHandle);

		Property->InitializeValue(Dest);

		Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FWeakObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto ObjectA = Property->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)))->Get();

		return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}

MonoObject* FWeakObjectPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	if (bIsCopy)
	{
		const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, true>(
			Object, InAddress);

		return Object;
	}
	else
	{
		auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TWeakObjectPtr<UObject>>(InAddress);

		if (Object == nullptr)
		{
			Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, false>(
				Object, InAddress);
		}

		return Object;
	}
}
