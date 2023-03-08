#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.h"
#include "mono/metadata/object-forward.h"

class FMultiRegistry
{
public:
	struct FSubclassOfAddress
	{
		void* Address;

		TSubclassOf<UObject> Class;
	};

public:
	FMultiRegistry();

	~FMultiRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	TSubclassOf<UObject> GetMulti(const MonoObject* InMonoObject);

	MonoObject* GetObject(const void* InAddress) const;

public:
	bool AddReference(MonoObject* InMonoObject, const TSubclassOf<UObject>& InClass);

	bool AddReference(void* InAddress, MonoObject* InMonoObject, const TSubclassOf<UObject>& InClass);

	bool RemoveReference(const MonoObject* InMonoObject);

	bool RemoveReference(const void* InAddress);

private:
	TGarbageCollectionHandleMapping<FSubclassOfAddress> GarbageCollectionHandle2SubclassOfAddress;

	TMap<void*, FGarbageCollectionHandle> SubclassOfAddress2GarbageCollectionHandle;
};
