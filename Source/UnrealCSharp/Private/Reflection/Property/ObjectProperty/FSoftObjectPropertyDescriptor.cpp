#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FSoftObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(
			SrcMonoObject);

		SoftObjectProperty->InitializeValue(Dest);

		if (SrcMulti != nullptr)
		{
			SoftObjectProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
		}
	}
}

bool FSoftObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (SoftObjectProperty != nullptr)
	{
		const auto ObjectA = SoftObjectProperty->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(
			static_cast<FGarbageCollectionHandle>(const_cast<void*>(B)))->Get();

		return SoftObjectProperty->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}

MonoObject* FSoftObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftObjectPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
