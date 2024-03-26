#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/PropertyMacro.h"

FClassPropertyDescriptor::FClassPropertyDescriptor(FProperty* InProperty):
	FObjectPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(ClassProperty);

	Property = FMonoDomain::Class_Get_Property_From_Name(Class, PROPERTY_GARBAGE_COLLECTION_HANDLE);
}

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

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
			FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(SrcMonoObject, Property));

		ClassProperty->InitializeValue(Dest);

		if (SrcMulti != nullptr)
		{
			ClassProperty->SetObjectPropertyValue(Dest, SrcMulti->Get());
		}
	}
}

bool FClassPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (ClassProperty != nullptr)
	{
		const auto ClassA = Cast<UClass>(ClassProperty->GetObjectPropertyValue(A));

		const auto ClassB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
			FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(static_cast<MonoObject*>(const_cast<void*>(B)), Property))->Get();

		return ClassProperty->StaticIdentical(ClassA, ClassB, PortFlags);
	}

	return false;
}

MonoObject* FClassPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(Object, InAddress, false);
	}

	return Object;
}
