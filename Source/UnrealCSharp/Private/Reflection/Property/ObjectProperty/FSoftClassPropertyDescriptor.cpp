#include "Reflection/Property/ObjectProperty/FSoftClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSoftClassPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftClassProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FSoftClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftClassProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
			SrcGarbageCollectionHandle);

		SoftClassProperty->InitializeValue(Dest);

		SoftClassProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
	}
}

bool FSoftClassPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (SoftClassProperty != nullptr)
	{
		const auto ClassA = SoftClassProperty->GetObjectPropertyValue(A);

		const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
			static_cast<FGarbageCollectionHandle>(const_cast<void*>(B)))->Get();

		return SoftClassProperty->StaticIdentical(ClassA, ClassB, PortFlags);
	}

	return false;
}

MonoObject* FSoftClassPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftClassPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
