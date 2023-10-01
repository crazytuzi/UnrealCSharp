#pragma once

#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

class UNREALCSHARP_API FObjectRegistry
{
public:
	template <typename Key>
	struct TObjectMapping : TValueMapping<Key>
	{
	};

	typedef TObjectMapping<TWeakObjectPtr<const UObject>> FObjectMapping;

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
	FObjectMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2Object;

	FObjectMapping::FKey2GarbageCollectionHandle Object2GarbageCollectionHandleMap;

	FObjectMapping::FMonoObject2Value MonoObject2Object;
};
