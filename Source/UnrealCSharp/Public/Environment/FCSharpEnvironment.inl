#pragma once

template <typename T>
T* FCSharpEnvironment::TGetAddress<UObject, T>::operator()(const FCSharpEnvironment* InEnvironment,
                                                           const FGarbageCollectionHandle& InGarbageCollectionHandle)
const
{
	if (InEnvironment != nullptr && InEnvironment->ObjectRegistry != nullptr)
	{
		if (const auto FoundObject = InEnvironment->ObjectRegistry->GetAddress(InGarbageCollectionHandle))
		{
			return static_cast<T*>(FoundObject);
		}
	}

	return nullptr;
}

template <typename T>
T* FCSharpEnvironment::TGetAddress<UObject, T>::operator()(const FCSharpEnvironment* InEnvironment,
                                                           const MonoObject* InMonoObject) const
{
	if (InEnvironment != nullptr && InEnvironment->ObjectRegistry != nullptr)
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
                                                                 const FGarbageCollectionHandle&
                                                                 InGarbageCollectionHandle) const
{
	if (InEnvironment != nullptr && InEnvironment->StructRegistry != nullptr)
	{
		if (const auto FoundStruct = InEnvironment->StructRegistry->GetAddress(InGarbageCollectionHandle))
		{
			return static_cast<T*>(FoundStruct);
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
auto FCSharpEnvironment::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return TGetAddress<T, U>()(this, InGarbageCollectionHandle);
}

template <>
inline void* FCSharpEnvironment::GetAddress<UObject>(const FGarbageCollectionHandle& InGarbageCollectionHandle,
                                                     UStruct*& InStruct) const
{
	if (ObjectRegistry != nullptr)
	{
		if (const auto FoundObject = ObjectRegistry->GetAddress(InGarbageCollectionHandle, InStruct))
		{
			return FoundObject;
		}
	}

	return nullptr;
}

template <>
inline void* FCSharpEnvironment::GetAddress<UScriptStruct>(const FGarbageCollectionHandle& InGarbageCollectionHandle,
                                                           UStruct*& InStruct) const
{
	if (StructRegistry != nullptr)
	{
		if (const auto FoundStruct = StructRegistry->GetAddress(InGarbageCollectionHandle, InStruct))
		{
			return FoundStruct;
		}
	}

	return nullptr;
}

template <typename T, typename U>
auto FCSharpEnvironment::GetAddress(const MonoObject* InMonoObject) const
{
	return TGetAddress<T, U>()(this, InMonoObject);
}

template <typename T>
auto FCSharpEnvironment::GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return ObjectRegistry != nullptr ? Cast<T>(ObjectRegistry->GetObject(InGarbageCollectionHandle)) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetObject(const MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? Cast<T>(ObjectRegistry->GetObject(InMonoObject)) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetContainer(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->GetContainer<T>(InGarbageCollectionHandle) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetContainer(const MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->GetContainer<T>(InMonoObject) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetDelegate(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->GetDelegate<T>(InGarbageCollectionHandle) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetMulti(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return MultiRegistry != nullptr
		       ? (T*)FMultiRegistry::TMultiRegistry<T, T>::GetMulti(MultiRegistry, InGarbageCollectionHandle)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetMulti(MonoObject* InMonoObject) const
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
auto FCSharpEnvironment::RemoveMultiReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::RemoveReference(MultiRegistry, InGarbageCollectionHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetBinding(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return BindingRegistry != nullptr
		       ? static_cast<T*>(BindingRegistry->GetObject(InGarbageCollectionHandle))
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::RemoveBindingReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return BindingRegistry != nullptr
		       ? BindingRegistry->RemoveReference<T>(InGarbageCollectionHandle)
		       : false;
}
