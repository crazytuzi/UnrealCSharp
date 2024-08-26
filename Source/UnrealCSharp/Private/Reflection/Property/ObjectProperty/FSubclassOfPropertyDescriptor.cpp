#include "Reflection/Property/ObjectProperty/FSubclassOfPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FSubclassOfPropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src, bIsCopy);
	}
}

void FSubclassOfPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
			SrcGarbageCollectionHandle);

		Property->InitializeValue(Dest);

		if (SrcMulti != nullptr)
		{
			Property->SetObjectPropertyValue(Dest, SrcMulti->Get());
		}
	}
}

bool FSubclassOfPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto ClassA = Cast<UClass>(Property->GetObjectPropertyValue(A));

		const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)))->Get();

		return Property->StaticIdentical(ClassA, ClassB, PortFlags);
	}

	return false;
}

MonoObject* FSubclassOfPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	if (bIsCopy)
	{
		const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, true>(
			Object, InAddress);

		return Object;
	}
	else
	{
		auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(InAddress);

		if (Object == nullptr)
		{
			Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, false>(
				Object, InAddress);
		}

		return Object;
	}
}
