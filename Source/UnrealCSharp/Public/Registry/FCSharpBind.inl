#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

template <auto IsNeedMonoClass>
auto FCSharpBind::Bind(FDomain* InDomain, UStruct* InStruct)
{
	if (FCSharpEnvironment::GetEnvironment().GetClassDescriptor(InStruct))
	{
		return true;
	}

	if constexpr (IsNeedMonoClass)
	{
		if (!CanBind(InStruct))
		{
			NotOverrideTypes.Add(InStruct);

			return false;
		}
	}

	return BindImplementation(InDomain, InStruct);
}

template <auto IsNeedMonoClass>
auto FCSharpBind::Bind(FDomain* InDomain, UObject* InObject)
{
	return BindImplementation<IsNeedMonoClass>(InDomain, InObject);
}

template <typename T>
auto FCSharpBind::Bind(MonoClass* InMonoClass, MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	return BindImplementation<T>(InMonoClass, InMonoObject, InReflectionType);
}

template <typename T>
auto FCSharpBind::Bind(MonoClass* InMonoClass, MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
                       MonoReflectionType* InValueReflectionType)
{
	return BindImplementation<T>(InMonoClass, InMonoObject, InKeyReflectionType, InValueReflectionType);
}

template <typename T>
auto FCSharpBind::Bind(MonoClass* InMonoClass, MonoObject* InMonoObject)
{
	return BindImplementation<T>(InMonoClass, InMonoObject);
}

template <auto IsNeedMonoClass>
auto FCSharpBind::BindImplementation(FDomain* InDomain, UObject* InObject) -> MonoObject*
{
	if (InDomain == nullptr || InObject == nullptr)
	{
		return nullptr;
	}

	const auto InClass = InObject->GetClass();

	if (InClass == nullptr)
	{
		return nullptr;
	}

	if (!Bind<IsNeedMonoClass>(InDomain, static_cast<UStruct*>(InClass)))
	{
		return nullptr;
	}

	const auto FoundClassDescriptor = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(InClass);

	if (FoundClassDescriptor == nullptr)
	{
		return nullptr;
	}

	const auto FoundMonoClass = FoundClassDescriptor->GetMonoClass();

	if (FoundMonoClass == nullptr)
	{
		return nullptr;
	}

	const auto NewMonoObject = InDomain->Object_New(FoundMonoClass);

	FCSharpEnvironment::GetEnvironment().AddObjectReference(InObject, NewMonoObject);

	return NewMonoObject;
}

template <typename T>
auto FCSharpBind::BindImplementation(MonoClass* InMonoClass, MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	const auto Property = FTypeBridge::Factory<>(InReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(Property, nullptr, true, true);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ContainerHelper, InMonoClass, InMonoObject);

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(MonoClass* InMonoClass, MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
                                     MonoReflectionType* InValueReflectionType)
{
	const auto KeyProperty = FTypeBridge::Factory<>(InKeyReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ValueProperty =
		FTypeBridge::Factory<>(InValueReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(KeyProperty, ValueProperty, nullptr, true, true);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ContainerHelper, InMonoClass, InMonoObject);

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(MonoClass* InMonoClass, MonoObject* InMonoObject)
{
	const auto Helper = new T();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(Helper, InMonoClass, InMonoObject);

	return true;
}
