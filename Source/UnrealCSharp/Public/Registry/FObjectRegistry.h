#pragma once

#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

class UNREALCSHARP_API FObjectRegistry
{
private:
	template <typename Key>
	struct TObjectMapping : TValueMapping<Key>
	{
		typedef typename TObjectMapping::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
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

	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct);

	MonoObject* GetObject(const UObject* InObject);

	UObject* GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	FGarbageCollectionHandle GetGarbageCollectionHandle(const UObject* InObject);

public:
	bool AddReference(UObject* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const UObject* InObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FObjectMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2Object;

	FObjectMapping::FAddress2GarbageCollectionHandle Object2GarbageCollectionHandleMap;
};
