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
	auto GetContainer(const MonoObject* InMonoObject);

	template <typename T>
	auto GetContainer(const void* InAddress);

	MonoObject* GetObject(const void* InAddress);

	bool AddReference(void* InContainer, MonoObject* InMonoObject, void* InAddress = nullptr);

	bool AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InContainer,
	                  MonoObject* InMonoObject);

	bool RemoveReference(const MonoObject* InMonoObject);

	bool RemoveReference(const void* InAddress);

private:
	TGarbageCollectionHandleMapping<FContainerAddress> GarbageCollectionHandle2ContainerAddress;

	TMap<FContainerAddress, FGarbageCollectionHandle> ContainerAddress2GarbageCollectionHandle;
};

#include "FContainerRegistry.inl"
