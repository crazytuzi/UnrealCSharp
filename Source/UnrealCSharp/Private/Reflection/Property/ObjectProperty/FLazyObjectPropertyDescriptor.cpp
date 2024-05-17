#include "Reflection/Property/ObjectProperty/FLazyObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FLazyObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FLazyObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(
			SrcGarbageCollectionHandle);

		Property->InitializeValue(Dest);

		Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FLazyObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto ObjectA = Property->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(
			static_cast<FGarbageCollectionHandle>(const_cast<void*>(B)))->Get();

		return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}

MonoObject* FLazyObjectPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TLazyObjectPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TLazyObjectPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
