﻿#include "Reflection/Property/ObjectProperty/FSoftClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "UEVersion.h"

FSoftClassPropertyDescriptor::FSoftClassPropertyDescriptor(FProperty* InProperty):
	FObjectPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(SoftClassProperty);
}

void FSoftClassPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftClassProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FSoftClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftClassProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(SrcMonoObject);

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
			static_cast<MonoObject*>(const_cast<void*>(B)))->Get();

#if UE_OBJECT_PROPERTY_STATIC_IDENTICAL
		return SoftClassProperty->StaticIdentical(ClassA, ClassB, PortFlags);
#else
		return ClassA == ClassB;
#endif
	}

	return false;
}

MonoObject* FSoftClassPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSoftClassPtr<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>>(Object, InAddress, false);
	}

	return Object;
}
