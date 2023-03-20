#pragma once

template <>
inline auto FMultiRegistry::GetMulti<FMultiRegistry::FSubclassOfAddress::Type>(const MonoObject* InMonoObject)
{
	const auto FoundSubclassOfAddress = GarbageCollectionHandle2SubclassOfAddress.Find(InMonoObject);

	return FoundSubclassOfAddress != nullptr ? FoundSubclassOfAddress->Value : FSubclassOfAddress::Type();
}

template <>
inline auto FMultiRegistry::GetMulti<FMultiRegistry::FWeakObjectPtrAddress::Type>(const MonoObject* InMonoObject)
{
	const auto FoundWeakObjectPtrAddress = GarbageCollectionHandle2WeakObjectPtrAddress.Find(InMonoObject);

	return FoundWeakObjectPtrAddress != nullptr ? FoundWeakObjectPtrAddress->Value : FWeakObjectPtrAddress::Type();
}

template <>
inline auto FMultiRegistry::GetMulti<FMultiRegistry::FLazyObjectPtrAddress::Type>(const MonoObject* InMonoObject)
{
	const auto FoundLazyObjectPtrAddress = GarbageCollectionHandle2LazyObjectPtrAddress.Find(InMonoObject);

	return FoundLazyObjectPtrAddress != nullptr ? FoundLazyObjectPtrAddress->Value : FLazyObjectPtrAddress::Type();
}

template <>
inline auto FMultiRegistry::GetMulti<FMultiRegistry::FSoftObjectPtrAddress::Type>(const MonoObject* InMonoObject)
{
	const auto FoundSoftObjectPtrAddress = GarbageCollectionHandle2SoftObjectPtrAddress.Find(InMonoObject);

	return FoundSoftObjectPtrAddress != nullptr ? FoundSoftObjectPtrAddress->Value : FSoftObjectPtrAddress::Type();
}

template <>
inline auto FMultiRegistry::GetMulti<FMultiRegistry::FScriptInterfaceAddress::Type>(const MonoObject* InMonoObject)
{
	const auto FoundScriptInterfaceAddress = GarbageCollectionHandle2ScriptInterfaceAddress.Find(InMonoObject);

	return FoundScriptInterfaceAddress != nullptr
		       ? FoundScriptInterfaceAddress->Value
		       : FScriptInterfaceAddress::Type();
}

template <>
inline auto FMultiRegistry::GetMulti<FMultiRegistry::FSoftClassPtrAddress::Type>(const MonoObject* InMonoObject)
{
	const auto FoundSoftClassPtrAddress = GarbageCollectionHandle2SoftClassPtrAddress.Find(InMonoObject);

	return FoundSoftClassPtrAddress != nullptr ? FoundSoftClassPtrAddress->Value : FSoftClassPtrAddress::Type();
}

template <>
inline auto FMultiRegistry::GetObject<FMultiRegistry::FSubclassOfAddress::Type>(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = SubclassOfAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

template <>
inline auto FMultiRegistry::GetObject<FMultiRegistry::FWeakObjectPtrAddress::Type>(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = WeakObjectPtrAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

template <>
inline auto FMultiRegistry::GetObject<FMultiRegistry::FLazyObjectPtrAddress::Type>(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = LazyObjectPtrAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

template <>
inline auto FMultiRegistry::GetObject<FMultiRegistry::FSoftObjectPtrAddress::Type>(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = SoftObjectPtrAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

template <>
inline auto FMultiRegistry::GetObject<FMultiRegistry::FScriptInterfaceAddress::Type>(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = ScriptInterfaceAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

template <>
inline auto FMultiRegistry::GetObject<FMultiRegistry::FSoftClassPtrAddress::Type>(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = SoftClassPtrAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

template <>
inline auto FMultiRegistry::AddReference(MonoObject* InMonoObject, const FSubclassOfAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2SubclassOfAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                  FSubclassOfAddress{nullptr, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(MonoObject* InMonoObject, const FWeakObjectPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2WeakObjectPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                     FWeakObjectPtrAddress{nullptr, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(MonoObject* InMonoObject, const FLazyObjectPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2LazyObjectPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                     FLazyObjectPtrAddress{nullptr, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(MonoObject* InMonoObject, const FSoftObjectPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2SoftObjectPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                     FSoftObjectPtrAddress{nullptr, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(MonoObject* InMonoObject, const FScriptInterfaceAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2ScriptInterfaceAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                       FScriptInterfaceAddress{nullptr, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(MonoObject* InMonoObject, const FSoftClassPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2SoftClassPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                    FSoftClassPtrAddress{nullptr, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject,
                                         const FSubclassOfAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	SubclassOfAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2SubclassOfAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                  FSubclassOfAddress{InAddress, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject,
                                         const FWeakObjectPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	WeakObjectPtrAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2WeakObjectPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                     FWeakObjectPtrAddress{InAddress, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject,
                                         const FLazyObjectPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	LazyObjectPtrAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2LazyObjectPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                     FLazyObjectPtrAddress{InAddress, InValue});

	return true;
}


template <>
inline auto FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject,
                                         const FSoftObjectPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	SoftObjectPtrAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2SoftObjectPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                     FSoftObjectPtrAddress{InAddress, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject,
                                         const FScriptInterfaceAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	ScriptInterfaceAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2ScriptInterfaceAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                       FScriptInterfaceAddress{InAddress, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject,
                                         const FSoftClassPtrAddress::Type& InValue)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	SoftClassPtrAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2SoftClassPtrAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                    FSoftClassPtrAddress{InAddress, InValue});

	return true;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FSubclassOfAddress::Type>(const MonoObject* InMonoObject)
{
	if (const auto FoundSubclassOfAddress = GarbageCollectionHandle2SubclassOfAddress.Find(InMonoObject))
	{
		SubclassOfAddress2GarbageCollectionHandle.Remove(FoundSubclassOfAddress->Address);

		GarbageCollectionHandle2SubclassOfAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FWeakObjectPtrAddress::Type>(const MonoObject* InMonoObject)
{
	if (const auto FoundWeakObjectPtrAddress = GarbageCollectionHandle2WeakObjectPtrAddress.Find(InMonoObject))
	{
		WeakObjectPtrAddress2GarbageCollectionHandle.Remove(FoundWeakObjectPtrAddress->Address);

		GarbageCollectionHandle2WeakObjectPtrAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FLazyObjectPtrAddress::Type>(const MonoObject* InMonoObject)
{
	if (const auto FoundLazyObjectPtrAddress = GarbageCollectionHandle2LazyObjectPtrAddress.Find(InMonoObject))
	{
		LazyObjectPtrAddress2GarbageCollectionHandle.Remove(FoundLazyObjectPtrAddress->Address);

		GarbageCollectionHandle2LazyObjectPtrAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FSoftObjectPtrAddress::Type>(const MonoObject* InMonoObject)
{
	if (const auto FoundSoftObjectPtrAddress = GarbageCollectionHandle2SoftObjectPtrAddress.Find(InMonoObject))
	{
		SoftObjectPtrAddress2GarbageCollectionHandle.Remove(FoundSoftObjectPtrAddress->Address);

		GarbageCollectionHandle2SoftObjectPtrAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FScriptInterfaceAddress::Type>(
	const MonoObject* InMonoObject)
{
	if (const auto FoundScriptInterfaceAddress = GarbageCollectionHandle2ScriptInterfaceAddress.Find(InMonoObject))
	{
		ScriptInterfaceAddress2GarbageCollectionHandle.Remove(FoundScriptInterfaceAddress->Address);

		GarbageCollectionHandle2ScriptInterfaceAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FSoftClassPtrAddress::Type>(const MonoObject* InMonoObject)
{
	if (const auto FoundSoftClassPtrAddress = GarbageCollectionHandle2SoftClassPtrAddress.Find(InMonoObject))
	{
		SoftClassPtrAddress2GarbageCollectionHandle.Remove(FoundSoftClassPtrAddress->Address);

		GarbageCollectionHandle2SoftClassPtrAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FSubclassOfAddress::Type>(const void* InAddress)
{
	for (const auto& Pair : SubclassOfAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			SubclassOfAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2SubclassOfAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FWeakObjectPtrAddress::Type>(const void* InAddress)
{
	for (const auto& Pair : WeakObjectPtrAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			WeakObjectPtrAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2WeakObjectPtrAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FLazyObjectPtrAddress::Type>(const void* InAddress)
{
	for (const auto& Pair : LazyObjectPtrAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			LazyObjectPtrAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2LazyObjectPtrAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FSoftObjectPtrAddress::Type>(const void* InAddress)
{
	for (const auto& Pair : SoftObjectPtrAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			SoftObjectPtrAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2SoftObjectPtrAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FScriptInterfaceAddress::Type>(const void* InAddress)
{
	for (const auto& Pair : ScriptInterfaceAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			ScriptInterfaceAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2ScriptInterfaceAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}

template <>
inline auto FMultiRegistry::RemoveReference<FMultiRegistry::FSoftClassPtrAddress::Type>(const void* InAddress)
{
	for (const auto& Pair : SoftClassPtrAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			SoftClassPtrAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2SoftClassPtrAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}
