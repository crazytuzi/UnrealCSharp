#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "GarbageCollection/TMonoObjectMapping.inl"

template <typename Key, typename Value = Key>
struct TValueMapping
{
	typedef TGarbageCollectionHandleMapping<Value> GarbageCollectionHandle2Value;

	typedef TMap<Key, typename TGarbageCollectionHandleMapping<Value>::KeyType> Value2GarbageCollectionHandle;

	typedef TMonoObjectMapping<Value> MonoObject2Value;
};
