#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftObjectPtr<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FSoftObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(SrcMonoObject);

		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftObjectPtr<UObject>>(Dest);

		SoftObjectProperty->InitializeValue(Dest);

		if (SrcMulti != nullptr)
		{
			SoftObjectProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
		}

		Object_New(Dest);
	}
}

bool FSoftObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (SoftObjectProperty != nullptr)
	{
		const auto ObjectA = SoftObjectProperty->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(
			static_cast<MonoObject*>(const_cast<void*>(B)))->Get();

#if UE_OBJECT_PROPERTY_STATIC_IDENTICAL
		return SoftObjectProperty->StaticIdentical(ObjectA, ObjectB, PortFlags);
#else
		return ObjectA == ObjectB;
#endif
	}

	return false;
}

MonoObject* FSoftObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(SoftObjectProperty);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>>(Object, InAddress, false);

	return Object;
}
