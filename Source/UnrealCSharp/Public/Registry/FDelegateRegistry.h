#pragma once

#include "mono/metadata/object-forward.h"

class FDelegateRegistry
{
public:
	FDelegateRegistry();

	~FDelegateRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	template <typename T>
	auto GetDelegate(const void* InAddress)
	{
		const auto FoundDelegate = Address2DelegateMap.Find(InAddress);

		return FoundDelegate != nullptr ? static_cast<T*>(*FoundDelegate) : nullptr;
	}

	template <typename T>
	MonoObject* GetObject(const T* InDelegate)
	{
		const auto FoundMonoObject = Delegate2MonoObjectMap.Find(InDelegate);

		return FoundMonoObject != nullptr ? *FoundMonoObject : nullptr;
	}

	bool AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject);

	template <typename T>
	bool RemoveReference(const MonoObject* InMonoObject)
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
	bool RemoveReference(const void* InAddress)
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

private:
	TMap<MonoObject*, void*> MonoObject2DelegateMap;

	TMap<void*, MonoObject*> Delegate2MonoObjectMap;

	TMap<void*, void*> Address2DelegateMap;
};
