#pragma once

template <typename T>
T* FCSharpEnvironment::TGetAddress<UObject, T>::operator()(const FCSharpEnvironment* InEnvironment,
                                                           const MonoObject* InMonoObject) const
{
	if (InEnvironment != nullptr && InEnvironment->ObjectRegistry == nullptr)
	{
		if (const auto FoundObject = InEnvironment->ObjectRegistry->GetAddress(InMonoObject))
		{
			return static_cast<T*>(FoundObject);
		}
	}

	return nullptr;
}

template <typename T>
T* FCSharpEnvironment::TGetAddress<UScriptStruct, T>::operator()(const FCSharpEnvironment* InEnvironment,
                                                                 const MonoObject* InMonoObject) const
{
	if (InEnvironment != nullptr && InEnvironment->StructRegistry != nullptr)
	{
		if (const auto FoundStruct = InEnvironment->StructRegistry->GetAddress(InMonoObject))
		{
			return static_cast<T*>(FoundStruct);
		}
	}

	return nullptr;
}

template <typename T, typename U>
auto FCSharpEnvironment::GetAddress(const MonoObject* InMonoObject) const
{
	return TGetAddress<T, U>()(this, InMonoObject);
}

template <>
inline void* FCSharpEnvironment::GetAddress<UObject>(const MonoObject* InMonoObject, UStruct*& InStruct) const
{
	if (ObjectRegistry != nullptr)
	{
		if (const auto FoundObject = ObjectRegistry->GetAddress(InMonoObject, InStruct))
		{
			return FoundObject;
		}
	}

	return nullptr;
}

template <>
inline void* FCSharpEnvironment::GetAddress<UScriptStruct>(const MonoObject* InMonoObject, UStruct*& InStruct) const
{
	if (StructRegistry != nullptr)
	{
		if (const auto FoundStruct = StructRegistry->GetAddress(InMonoObject, InStruct))
		{
			return FoundStruct;
		}
	}

	return nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetObject(const MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? Cast<T>(ObjectRegistry->GetObject(InMonoObject)) : nullptr;
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
auto FCSharpEnvironment::GetDelegate(const MonoObject* InMonoObject) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->GetDelegate<T>(InMonoObject) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetMulti(const MonoObject* InMonoObject) const
{
	return MultiRegistry != nullptr
		       ? (T*)FMultiRegistry::TMultiRegistry<T, T>::GetMulti(MultiRegistry, InMonoObject)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetMultiObject(const void* InAddress) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::GetObject(MultiRegistry, InAddress)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::AddMultiReference(MonoObject* InMonoObject, void* InValue, const bool bNeedFree) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::AddReference(MultiRegistry, InMonoObject, InValue, bNeedFree)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::RemoveMultiReference(const MonoObject* InMonoObject) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::RemoveReference(MultiRegistry, InMonoObject)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::RemoveMultiReference(const void* InAddress) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::RemoveReference(MultiRegistry, InAddress)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetBinding(const MonoObject* InMonoObject) const
{
	return BindingRegistry != nullptr ? static_cast<T*>(BindingRegistry->GetObject(InMonoObject)) : nullptr;
}
