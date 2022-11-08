#pragma once

#include "mono/metadata/object-forward.h"

class FContainerRegistry
{
public:
	FContainerRegistry();

	~FContainerRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	template <typename T>
	auto GetContainer(const MonoObject* InMonoObject)
	{
		const auto FoundContainer = MonoObject2ContainerMap.Find(InMonoObject);

		return FoundContainer != nullptr ? static_cast<T*>(*FoundContainer) : nullptr;
	}

	template <typename T>
	auto GetContainer(const void* InAddress)
	{
		const auto FoundContainer = Address2ContainerMap.Find(InAddress);

		return FoundContainer != nullptr ? static_cast<T*>(*FoundContainer) : nullptr;
	}

	template <typename T>
	MonoObject* GetObject(const T* InContainer)
	{
		const auto FoundMonoObject = Container2MonoObjectMap.Find(InContainer);

		return FoundMonoObject != nullptr ? *FoundMonoObject : nullptr;
	}

	bool AddReference(void* InContainer, MonoObject* InMonoObject);

	bool AddReference(void* InAddress, void* InContainer, MonoObject* InMonoObject);

	template <typename T>
	bool RemoveReference(const MonoObject* InMonoObject)
	{
		if (const auto FoundContainer = MonoObject2ContainerMap.Find(InMonoObject))
		{
			Container2MonoObjectMap.Remove(FoundContainer);

			delete static_cast<T*>(*FoundContainer);

			MonoObject2ContainerMap.Remove(InMonoObject);

			return true;
		}

		return false;
	}

	template <typename T>
	bool RemoveReference(const void* InAddress)
	{
		if (const auto FoundContainer = Address2ContainerMap.Find(InAddress))
		{
			Address2ContainerMap.Remove(InAddress);

			if (const auto FoundMonoObject = Container2MonoObjectMap.Find(FoundContainer))
			{
				MonoObject2ContainerMap.Remove(*FoundMonoObject);
			}

			Container2MonoObjectMap.Remove(FoundContainer);

			delete static_cast<T*>(*FoundContainer);

			return true;
		}

		return false;
	}

private:
	TMap<MonoObject*, void*> MonoObject2ContainerMap;

	TMap<void*, MonoObject*> Container2MonoObjectMap;

	TMap<void*, void*> Address2ContainerMap;
};
