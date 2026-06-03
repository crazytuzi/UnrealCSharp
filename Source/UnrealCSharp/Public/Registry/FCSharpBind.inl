#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Domain/Script/IManagedHandle.h"
#include "Registry/FClassRegistry.h"

template <auto IsNeedOverride>
auto FCSharpBind::Bind(UStruct* InStruct)
{
	if (FCSharpEnvironment::GetEnvironment().GetClassDescriptor(InStruct))
	{
		return true;
	}

	if constexpr (IsNeedOverride)
	{
		if (!CanBind(InStruct))
		{
			NotOverrideTypes.Add(InStruct);

			return false;
		}
	}

	return BindImplementation(InStruct);
}

template <auto IsNeedOverride>
auto FCSharpBind::Bind(UObject* InObject)
{
	return BindImplementation<IsNeedOverride>(InObject);
}

template <typename T>
auto FCSharpBind::Bind(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
                       const IManagedObject InManagedObject)
{
	return BindImplementation<T>(InClassReflection, InPropertyClassReflection, InManagedObject);
}

template <typename T>
auto FCSharpBind::Bind(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
                       FClassReflection* InValueClassReflection, const IManagedObject InManagedObject)
{
	return BindImplementation<T>(InClassReflection, InKeyClassReflection, InValueClassReflection, InManagedObject);
}

template <typename T>
auto FCSharpBind::Bind(FClassReflection* InClassReflection, const IManagedObject InManagedObject)
{
	return BindImplementation<T>(InClassReflection, InManagedObject);
}

template <auto IsNeedOverride>
auto FCSharpBind::BindImplementation(UObject* InObject) -> IManagedObject
{
	if (InObject == nullptr)
	{
		return INVALID_MANAGED;
	}

	const auto Class = InObject->GetClass();

	if (Class == nullptr)
	{
		return INVALID_MANAGED;
	}

	if (!Bind<IsNeedOverride>(static_cast<UStruct*>(Class)))
	{
		return INVALID_MANAGED;
	}

	const auto FoundClass = FReflectionRegistry::Get().GetClass(Class);

	if (FoundClass == nullptr)
	{
		return INVALID_MANAGED;
	}

	const auto NewObject = FoundClass->NewObject();

	FCSharpEnvironment::GetEnvironment().AddObjectReference(FoundClass, InObject, NewObject);

	return IManagedHandleToIManagedObject(NewObject);
}

template <typename T>
auto FCSharpBind::BindImplementation(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
                                     const IManagedObject InManagedObject)
{
	const auto Property = FTypeBridge::Factory<>(InPropertyClassReflection, nullptr, "", EObjectFlags::RF_Transient);

	Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(Property, nullptr, true, true);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(
		ContainerHelper, InClassReflection, MANAGED_HANDLE_FROM_OBJECT(InManagedObject));

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
                                     FClassReflection* InValueClassReflection, const IManagedObject InManagedObject)
{
	const auto KeyProperty = FTypeBridge::Factory<>(InKeyClassReflection, nullptr, "", EObjectFlags::RF_Transient);

	KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ValueProperty =
		FTypeBridge::Factory<>(InValueClassReflection, nullptr, "", EObjectFlags::RF_Transient);

	ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(KeyProperty, ValueProperty, nullptr, true, true);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(
		ContainerHelper, InClassReflection, MANAGED_HANDLE_FROM_OBJECT(InManagedObject));

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(FClassReflection* InClassReflection, const IManagedObject InManagedObject)
{
	const auto Helper = new T();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(
		Helper, InClassReflection, MANAGED_HANDLE_FROM_OBJECT(InManagedObject));

	return true;
}
