#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "mono/metadata/object-forward.h"

class UNREALCSHARP_API FObjectRegistry
{
public:
	FObjectRegistry();

	~FObjectRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	void* GetAddress(const MonoObject* InMonoObject);

	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct);

	MonoObject* GetObject(const UObject* InObject);

	UObject* GetObject(const MonoObject* InMonoObject);

	FGarbageCollectionHandle GetGarbageCollectionHandle(const UObject* InObject);

public:
	bool AddReference(UObject* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const UObject* InObject);

	bool RemoveReference(const MonoObject* InMonoObject);

private:
	TGarbageCollectionHandleMapping<TWeakObjectPtr<const UObject>> GarbageCollectionHandle2Object;

	TMap<TWeakObjectPtr<const UObject>, FGarbageCollectionHandle> Object2GarbageCollectionHandleMap;
};
