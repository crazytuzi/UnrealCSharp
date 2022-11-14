#pragma once

template <typename T>
auto FDelegateRegistry::GetDelegate(const void* InAddress)
{
	const auto FoundDelegate = Address2DelegateMap.Find(InAddress);

	return FoundDelegate != nullptr ? static_cast<T*>(*FoundDelegate) : nullptr;
}

template <typename T>
auto FDelegateRegistry::GetObject(const T* InDelegate)
{
	const auto FoundMonoObject = Delegate2MonoObjectMap.Find(InDelegate);

	return FoundMonoObject != nullptr ? *FoundMonoObject : nullptr;
}

template <typename T>
auto FDelegateRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundDelegate = MonoObject2DelegateMap.Find(InMonoObject))
	{
		Delegate2MonoObjectMap.Remove(FoundDelegate);

		delete static_cast<T*>(*FoundDelegate);

		MonoObject2DelegateMap.Remove(InMonoObject);

		return true;
	}

	return false;
}

template <typename T>
auto FDelegateRegistry::RemoveReference(const void* InAddress)
{
	if (const auto FoundDelegate = Address2DelegateMap.Find(InAddress))
	{
		Address2DelegateMap.Remove(InAddress);

		if (const auto FoundMonoObject = Delegate2MonoObjectMap.Find(FoundDelegate))
		{
			MonoObject2DelegateMap.Remove(*FoundMonoObject);
		}

		Delegate2MonoObjectMap.Remove(FoundDelegate);

		delete static_cast<T*>(*FoundDelegate);

		return true;
	}

	return false;
}
