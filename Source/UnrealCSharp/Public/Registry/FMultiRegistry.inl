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
