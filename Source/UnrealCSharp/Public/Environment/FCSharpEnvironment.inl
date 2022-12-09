#pragma once

template <typename T>
auto FCSharpEnvironment::Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType) const
{
	return FCSharpBind::Bind<T>(InMonoObject, InReflectionType);
}

template <typename T>
auto FCSharpEnvironment::GetContainer(const MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->GetContainer<T>(InMonoObject) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetContainer(const void* InAddress) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->GetContainer<T>(InAddress) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::RemoveContainerReference(const MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->RemoveReference<T>(InMonoObject) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::RemoveContainerReference(const void* InContainer) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->RemoveReference<T>(InContainer) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetDelegate(const void* InAddress) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->GetDelegate<T>(InAddress) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::RemoveDelegateReference(const MonoObject* InMonoObject) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->RemoveReference<T>(InMonoObject) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::RemoveDelegateReference(const void* InDelegate) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->RemoveReference<T>(InDelegate) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetBinding(const MonoObject* InMonoObject) const
{
	return BindingRegistry != nullptr ? BindingRegistry->GetBinding<T>(InMonoObject) : nullptr;
}
