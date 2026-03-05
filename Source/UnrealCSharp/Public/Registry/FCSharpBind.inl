#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

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
                       MonoObject* InMonoObject)
{
	return BindImplementation<T>(InClassReflection, InPropertyClassReflection, InMonoObject);
}

template <typename T>
auto FCSharpBind::Bind(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
                       FClassReflection* InValueClassReflection, MonoObject* InMonoObject)
{
	return BindImplementation<T>(InClassReflection, InKeyClassReflection, InValueClassReflection, InMonoObject);
}

template <typename T>
auto FCSharpBind::Bind(FClassReflection* InClassReflection, MonoObject* InMonoObject)
{
	return BindImplementation<T>(InClassReflection, InMonoObject);
}

template <auto IsNeedOverride>
auto FCSharpBind::BindImplementation(UObject* InObject) -> MonoObject*
{
	if (InObject == nullptr)
	{
		return nullptr;
	}

	const auto InClass = InObject->GetClass();

	if (InClass == nullptr)
	{
		return nullptr;
	}

	if (!Bind<IsNeedOverride>(static_cast<UStruct*>(InClass)))
	{
		return nullptr;
	}

	const auto FoundClass = FReflectionRegistry::Get().GetClass(InClass);

	if (FoundClass == nullptr)
	{
		return nullptr;
	}

	const auto NewObject = FoundClass->NewObject();

	FCSharpEnvironment::GetEnvironment().AddObjectReference(FoundClass, InObject, NewObject);

	return NewObject;
}

template <typename T>
auto FCSharpBind::BindImplementation(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
                                     MonoObject* InMonoObject)
{
	const auto Property = FTypeBridge::Factory<>(InPropertyClassReflection, nullptr, "", EObjectFlags::RF_Transient);

	Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(Property, nullptr, true, true);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ContainerHelper, InClassReflection, InMonoObject);

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
                                     FClassReflection* InValueClassReflection, MonoObject* InMonoObject)
{
	const auto KeyProperty = FTypeBridge::Factory<>(InKeyClassReflection, nullptr, "", EObjectFlags::RF_Transient);

	KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ValueProperty =
		FTypeBridge::Factory<>(InValueClassReflection, nullptr, "", EObjectFlags::RF_Transient);

	ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(KeyProperty, ValueProperty, nullptr, true, true);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ContainerHelper, InClassReflection, InMonoObject);

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(FClassReflection* InClassReflection, MonoObject* InMonoObject)
{
	const auto Helper = new T();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(Helper, InClassReflection, InMonoObject);

	return true;
}
