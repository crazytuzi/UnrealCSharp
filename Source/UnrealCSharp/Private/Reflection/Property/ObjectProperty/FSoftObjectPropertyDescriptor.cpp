#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>, true>(
		Object, Src);

	*Dest = Object;
}

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftObjectPtr<UObject>>(Src);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>, false>(
			Object, Src);
	}

	*Dest = Object;
}

void FSoftObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(
		SrcGarbageCollectionHandle);

	Property->InitializeValue(Dest);

	if (SrcMulti != nullptr)
	{
		Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FSoftObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto ObjectA = Property->GetObjectPropertyValue(A);

	const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)))->Get();

	return Property->StaticIdentical(ObjectA, ObjectB, PortFlags);
}
