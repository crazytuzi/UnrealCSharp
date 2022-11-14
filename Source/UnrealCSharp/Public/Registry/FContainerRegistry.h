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
	auto GetContainer(const MonoObject* InMonoObject);

	template <typename T>
	auto GetContainer(const void* InAddress);

	template <typename T>
	auto GetObject(const T* InContainer);

	bool AddReference(void* InContainer, MonoObject* InMonoObject);

	bool AddReference(void* InAddress, void* InContainer, MonoObject* InMonoObject);

	template <typename T>
	auto RemoveReference(const MonoObject* InMonoObject);

	template <typename T>
	auto RemoveReference(const void* InAddress);

private:
	TMap<MonoObject*, void*> MonoObject2ContainerMap;

	TMap<void*, MonoObject*> Container2MonoObjectMap;

	TMap<void*, void*> Address2ContainerMap;
};

#include "FContainerRegistry.inl"
