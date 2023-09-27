#pragma once

#include "TAddress.inl"
#include "TValueMapping.inl"
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
	TValueMapping<TWeakObjectPtr<const UObject>>::GarbageCollectionHandle2Value GarbageCollectionHandle2Object;

	TValueMapping<TWeakObjectPtr<const UObject>>::Value2GarbageCollectionHandle Object2GarbageCollectionHandleMap;

	TValueMapping<TWeakObjectPtr<const UObject>>::MonoObject2Value MonoObject2Object;
};
