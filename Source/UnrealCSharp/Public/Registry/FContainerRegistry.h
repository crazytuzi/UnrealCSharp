#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "Reflection/Container/FContainerHelper.h"
#include "mono/metadata/object-forward.h"

struct FContainerAddress
{
	void* Address;

	FContainerHelper* ContainerHelper;
};

static bool operator==(const FContainerAddress& A, const FContainerAddress& B);

static bool operator==(const FContainerAddress& A, const void* B);

static uint32 GetTypeHash(const FContainerAddress& InContainerAddress);

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
	auto GetContainer(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	template <typename T>
	auto GetContainer(const MonoObject* InMonoObject);

	MonoObject* GetObject(const void* InAddress);

	bool AddReference(void* InAddress, void* InContainer, MonoObject* InMonoObject);

	bool AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InContainer,
	                  MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<FContainerAddress> GarbageCollectionHandle2ContainerAddress;

	TMap<FContainerAddress, FGarbageCollectionHandle> ContainerAddress2GarbageCollectionHandle;

	TMap<void*, FGarbageCollectionHandle> Address2GarbageCollectionHandle;

	TMap<MonoObject*, FGarbageCollectionHandle> MonoObject2GarbageCollectionHandleMap;
};

#include "FContainerRegistry.inl"
