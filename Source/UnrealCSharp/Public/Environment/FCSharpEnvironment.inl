#pragma once

#include "Registry/FContainerRegistry.h"
#include "Registry/FDelegateRegistry.h"
#include "Registry/FBindingRegistry.h"
#include "Registry/FCSharpBind.h"
#include "Domain/Script/IManagedHandle.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Registry/FOptionalRegistry.h"
#endif

template <auto IsNeedOverride>
auto FCSharpEnvironment::Bind(UStruct* InStruct) const
{
	return FCSharpBind::Bind<IsNeedOverride>(InStruct);
}

template <auto IsNeedOverride>
auto FCSharpEnvironment::Bind(UObject* Object) const
{
	return FCSharpBind::Bind<IsNeedOverride>(Object);
}

template <typename T>
auto FCSharpEnvironment::GetFunctionDescriptor(const uint32 InFunctionHash) const -> T*
{
	return ClassRegistry != nullptr ? ClassRegistry->GetFunctionDescriptor<T>(InFunctionHash) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetOrAddFunctionDescriptor(const uint32 InFunctionHash) const -> T*
{
	return ClassRegistry != nullptr ? ClassRegistry->GetOrAddFunctionDescriptor<T>(InFunctionHash) : nullptr;
}

template <typename T, typename... Args>
auto FCSharpEnvironment::AddFunctionHash(Args&&... InArgs) const -> void
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->AddFunctionHash<T>(std::forward<Args>(InArgs)...);
	}
}

template <typename T>
auto FCSharpEnvironment::TGetAddress<UObject, T>::operator()(const FCSharpEnvironment* InEnvironment,
                                                             const IManagedHandle InManagedHandle) const -> T*
{
	if (InEnvironment != nullptr && InEnvironment->ObjectRegistry != nullptr)
	{
		if (const auto FoundObject = InEnvironment->ObjectRegistry->GetAddress(InManagedHandle))
		{
			return static_cast<T*>(FoundObject);
		}
	}

	return nullptr;
}

template <typename T>
auto FCSharpEnvironment::TGetAddress<UScriptStruct, T>::operator()(const FCSharpEnvironment* InEnvironment,
                                                                   const IManagedHandle InManagedHandle) const -> T*
{
	if (InEnvironment != nullptr && InEnvironment->StructRegistry != nullptr)
	{
		if (const auto FoundStruct = InEnvironment->StructRegistry->GetAddress(InManagedHandle))
		{
			return static_cast<T*>(FoundStruct);
		}
	}

	return nullptr;
}

template <typename T, typename U>
auto FCSharpEnvironment::GetAddress(const IManagedHandle InManagedHandle) const
{
	return TGetAddress<T, U>()(this, InManagedHandle);
}

template <>
inline auto FCSharpEnvironment::GetAddress<UObject>(const IManagedHandle InManagedHandle,
                                                    UStruct*& InStruct) const -> void*
{
	if (ObjectRegistry != nullptr)
	{
		if (const auto FoundObject = ObjectRegistry->GetAddress(InManagedHandle, InStruct))
		{
			return FoundObject;
		}
	}

	return nullptr;
}

template <>
inline void* FCSharpEnvironment::GetAddress<UScriptStruct>(const IManagedHandle InManagedHandle,
                                                           UStruct*& InStruct) const
{
	if (StructRegistry != nullptr)
	{
		if (const auto FoundStruct = StructRegistry->GetAddress(InManagedHandle, InStruct))
		{
			return FoundStruct;
		}
	}

	return nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetObject(const IManagedHandle InManagedHandle) const
{
	return ObjectRegistry != nullptr ? Cast<T>(ObjectRegistry->GetObject(InManagedHandle)) : nullptr;
}

template <auto IsNeedFree>
auto FCSharpEnvironment::AddStructReference(UScriptStruct* InScriptStruct, const void* InStruct,
                                            const IManagedHandle InManagedHandle) const
{
	return StructRegistry != nullptr
		       ? StructRegistry->AddReference<IsNeedFree>(InScriptStruct, InStruct, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetStruct(const IManagedHandle InManagedHandle) const -> T*
{
	return StructRegistry != nullptr ? static_cast<T*>(StructRegistry->GetStruct(InManagedHandle)) : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetContainer(const IManagedHandle InManagedHandle) const
{
	return ContainerRegistry != nullptr
		       ? FContainerRegistry::TContainerRegistry<T>::GetContainer(ContainerRegistry, InManagedHandle)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetContainerObject(void* InAddress) const
{
	return ContainerRegistry != nullptr
		       ? FContainerRegistry::TContainerRegistry<T>::GetObject(ContainerRegistry, InAddress)
		       : InvalidManagedHandle;
}

template <typename T>
auto FCSharpEnvironment::AddContainerReference(T* InValue, FClassReflection* InClass,
                                               IManagedHandle InManagedHandle) const
{
	return ContainerRegistry != nullptr
		       ? FContainerRegistry::TContainerRegistry<T>::AddReference(
			       ContainerRegistry, InValue, InClass, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::AddContainerReference(const IManagedHandle InOwner, void* InAddress, T* InValue,
                                               FClassReflection* InClass, IManagedHandle InManagedHandle) const
{
	return ContainerRegistry != nullptr
		       ? FContainerRegistry::TContainerRegistry<T>::AddReference(
			       ContainerRegistry, InOwner, InAddress, InValue, InClass, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::RemoveContainerReference(const IManagedHandle InManagedHandle) const
{
	return ContainerRegistry != nullptr
		       ? FContainerRegistry::TContainerRegistry<T>::RemoveReference(
			       ContainerRegistry, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetDelegate(const IManagedHandle InManagedHandle) const
{
	return DelegateRegistry != nullptr
		       ? FDelegateRegistry::TDelegateRegistry<T>::GetDelegate(DelegateRegistry, InManagedHandle)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetDelegateObject(void* InAddress) const
{
	return DelegateRegistry != nullptr
		       ? FDelegateRegistry::TDelegateRegistry<T>::GetObject(DelegateRegistry, InAddress)
		       : InvalidManagedHandle;
}

template <typename T>
auto FCSharpEnvironment::AddDelegateReference(T* InValue, FClassReflection* InClass,
                                              const IManagedHandle InManagedHandle) const
{
	return DelegateRegistry != nullptr
		       ? FDelegateRegistry::TDelegateRegistry<T>::AddReference(
			       DelegateRegistry, InValue, InClass, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::AddDelegateReference(const IManagedHandle InOwner, void* InAddress, T* InValue,
                                              FClassReflection* InClass, const IManagedHandle InManagedHandle) const
{
	return DelegateRegistry != nullptr
		       ? FDelegateRegistry::TDelegateRegistry<T>::AddReference(
			       DelegateRegistry, InOwner, InAddress, InValue, InClass, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::RemoveDelegateReference(const IManagedHandle InManagedHandle) const
{
	return DelegateRegistry != nullptr
		       ? FDelegateRegistry::TDelegateRegistry<T>::RemoveReference(DelegateRegistry, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetMulti(const IManagedHandle InManagedHandle) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::GetMulti(MultiRegistry, InManagedHandle)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetMultiObject(void* InAddress) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::GetObject(MultiRegistry, InAddress)
		       : InvalidManagedHandle;
}

template <typename T, auto IsNeedFree, auto IsMember>
auto FCSharpEnvironment::AddMultiReference(FClassReflection* InClass, const IManagedHandle InManagedHandle,
                                           void* InValue) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::template AddReference<IsNeedFree, IsMember>(
			       MultiRegistry, InClass, InManagedHandle, InValue)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::RemoveMultiReference(const IManagedHandle InManagedHandle) const
{
	return MultiRegistry != nullptr
		       ? FMultiRegistry::TMultiRegistry<T, T>::RemoveReference(MultiRegistry, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetString(const IManagedHandle InManagedHandle) const
{
	return StringRegistry != nullptr
		       ? FStringRegistry::TStringRegistry<T>::GetString(StringRegistry, InManagedHandle)
		       : nullptr;
}

template <typename T>
auto FCSharpEnvironment::GetStringObject(void* InAddress) const
{
	return StringRegistry != nullptr
		       ? FStringRegistry::TStringRegistry<T>::GetObject(StringRegistry, InAddress)
		       : InvalidManagedHandle;
}

template <typename T, auto IsNeedFree, auto IsMember>
auto FCSharpEnvironment::AddStringReference(FClassReflection* InClass, const IManagedHandle InManagedHandle,
                                            void* InValue) const
{
	return StringRegistry != nullptr
		       ? FStringRegistry::TStringRegistry<T>::template AddReference<IsNeedFree, IsMember>(
			       StringRegistry, InClass, InManagedHandle, InValue)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::RemoveStringReference(const IManagedHandle InManagedHandle) const
{
	return StringRegistry != nullptr
		       ? FStringRegistry::TStringRegistry<T>::RemoveReference(StringRegistry, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetBinding(const IManagedHandle InManagedHandle) const
{
	return BindingRegistry != nullptr
		       ? BindingRegistry->GetBinding<T>(InManagedHandle)
		       : nullptr;
}

template <typename T, auto IsNeedFree>
auto FCSharpEnvironment::AddBindingReference(FClassReflection* InClass, const IManagedHandle InManagedHandle,
                                             const T* InObject) const
{
	return BindingRegistry != nullptr
		       ? BindingRegistry->AddReference<T, IsNeedFree>(InObject, InClass, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::AddBindingReference(const IManagedHandle InOwner, FClassReflection* InClass,
                                             const IManagedHandle InManagedHandle, const T* InObject) const
{
	return BindingRegistry != nullptr
		       ? BindingRegistry->AddReference(InOwner, InObject, InClass, InManagedHandle)
		       : false;
}

template <typename T>
auto FCSharpEnvironment::GetRegistry()
{
	if constexpr (std::is_same_v<T, FDynamicRegistry>)
	{
		return DynamicRegistry;
	}
	else if constexpr (std::is_same_v<T, FClassRegistry>)
	{
		return ClassRegistry;
	}
	else if constexpr (std::is_same_v<T, FReferenceRegistry>)
	{
		return ReferenceRegistry;
	}
	else if constexpr (std::is_same_v<T, FObjectRegistry>)
	{
		return ObjectRegistry;
	}
	else if constexpr (std::is_same_v<T, FStructRegistry>)
	{
		return StructRegistry;
	}
	else if constexpr (std::is_same_v<T, FContainerRegistry>)
	{
		return ContainerRegistry;
	}
	else if constexpr (std::is_same_v<T, FDelegateRegistry>)
	{
		return DelegateRegistry;
	}
	else if constexpr (std::is_same_v<T, FMultiRegistry>)
	{
		return MultiRegistry;
	}
	else if constexpr (std::is_same_v<T, FStringRegistry>)
	{
		return StringRegistry;
	}
	else if constexpr (std::is_same_v<T, FBindingRegistry>)
	{
		return BindingRegistry;
	}
#if UE_F_OPTIONAL_PROPERTY
	else if constexpr (std::is_same_v<T, FOptionalRegistry>)
	{
		return OptionalRegistry;
	}
#endif
}

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
auto FCSharpEnvironment::GetOptionalObject(void* InAddress) const
{
	return OptionalRegistry != nullptr
		       ? OptionalRegistry->GetObject(InAddress)
		       : InvalidManagedHandle;
}

template <typename T, auto IsMember>
auto FCSharpEnvironment::AddOptionalReference(void* InAddress, T* InValue, FClassReflection* InClass,
                                              const IManagedHandle InManagedHandle) const
{
	return OptionalRegistry != nullptr
		       ? OptionalRegistry->AddReference<IsMember>(InAddress, InValue, InClass, InManagedHandle)
		       : false;
}
#endif
