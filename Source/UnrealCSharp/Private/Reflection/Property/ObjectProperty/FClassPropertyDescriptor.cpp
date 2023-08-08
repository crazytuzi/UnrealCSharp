#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

void FClassPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ClassProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ClassProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(SrcMonoObject);

		ClassProperty->InitializeValue(Dest);

		if (SrcMulti != nullptr)
		{
			ClassProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
		}

		Object_New(Dest);
	}
}

bool FClassPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (ClassProperty != nullptr)
	{
		const auto ClassA = Cast<UClass>(ClassProperty->GetObjectPropertyValue(A));

		const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
			static_cast<MonoObject*>(const_cast<void*>(B)))->Get();

#if UE_OBJECT_PROPERTY_STATIC_IDENTICAL
		return ClassProperty->StaticIdentical(ClassA, ClassB, PortFlags);
#else
		return ClassA == ClassB;
#endif
	}

	return false;
}

MonoObject* FClassPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(InAddress);

	if (Object == nullptr)
	{
		const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(ClassProperty);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(Object, InAddress, false);
	}

	return Object;
}
