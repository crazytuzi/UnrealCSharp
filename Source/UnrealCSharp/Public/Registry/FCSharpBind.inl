#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

template <typename T>
auto FCSharpBind::Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	return BindImplementation<T>(InMonoObject, InReflectionType);
}

template <typename T>
auto FCSharpBind::Bind(MonoObject* InMonoObject)
{
	return BindImplementation<T>(InMonoObject);
}

template <typename T>
auto FCSharpBind::BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	const auto Property = FTypeBridge::Factory(InReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(Property);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ContainerHelper, InMonoObject);

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(MonoObject* InMonoObject)
{
	const auto Helper = new T();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(Helper, Helper, InMonoObject);

	return true;
}
