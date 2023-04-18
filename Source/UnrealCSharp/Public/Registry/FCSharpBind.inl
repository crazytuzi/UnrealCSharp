#pragma once

#include "Environment/FCSharpEnvironment.h"

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
	const auto Property = FContainerHelper::Factory(InReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ContainerHelper = new T(Property);

	FCSharpEnvironment::GetEnvironment()->AddContainerReference(ContainerHelper, InMonoObject);

	return true;
}

template <typename T>
auto FCSharpBind::BindImplementation(MonoObject* InMonoObject)
{
	const auto Object = NewObject<typename T::UHandlerType>();

	Object->AddToRoot();

	const auto DelegateHelper = new T(new FScriptDelegate(), Object->GetCallBack());

	FCSharpEnvironment::GetEnvironment()->AddDelegateReference(Object, DelegateHelper, InMonoObject);

	return true;
}
