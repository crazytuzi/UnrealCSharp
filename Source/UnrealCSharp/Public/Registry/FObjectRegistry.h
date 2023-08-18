#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "GarbageCollection/TMonoObjectMapping.inl"
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
	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	void* GetAddress(const MonoObject* InMonoObject);

	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct);

	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct);

	MonoObject* GetObject(const UObject* InObject);

	UObject* GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	UObject* GetObject(const MonoObject* InMonoObject);

	FGarbageCollectionHandle GetGarbageCollectionHandle(const UObject* InObject);

public:
	bool AddReference(UObject* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const UObject* InObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<TWeakObjectPtr<const UObject>> GarbageCollectionHandle2Object;

	TMap<TWeakObjectPtr<const UObject>, FGarbageCollectionHandle> Object2GarbageCollectionHandleMap;

	TMonoObjectMapping<TWeakObjectPtr<const UObject>> MonoObject2Object;
};
