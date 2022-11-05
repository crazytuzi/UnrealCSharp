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

	bool AddReference(void* InContainer, MonoObject* InMonoObject, bool bNeedFree = true);

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

private:
	TMap<MonoObject*, void*> MonoObject2ContainerMap;

	TMap<void*, MonoObject*> Container2MonoObjectMap;
};
