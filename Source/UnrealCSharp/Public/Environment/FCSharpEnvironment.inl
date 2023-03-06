#pragma once

template <typename T>
auto FCSharpEnvironment::Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType) const
{
	return FCSharpBind::Bind<T>(InMonoObject, InReflectionType);
}

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
U* FCSharpEnvironment::GetAddress(const MonoObject* InMonoObject) const
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
T* FCSharpEnvironment::GetObject(const MonoObject* InMonoObject) const
{
	return Cast<T>(GetObject(InMonoObject));
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
