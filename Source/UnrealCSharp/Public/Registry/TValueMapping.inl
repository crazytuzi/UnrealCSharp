#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "GarbageCollection/TMonoObjectMapping.inl"

template <typename Key, typename Value = Key>
struct TValueMapping
{
	typedef Key KeyType;

	typedef Value ValueType;

	typedef TGarbageCollectionHandleMapping<ValueType> FGarbageCollectionHandle2Value;

	typedef TMap<KeyType, typename FGarbageCollectionHandle2Value::KeyType> FKey2GarbageCollectionHandle;

	typedef TMonoObjectMapping<ValueType> FMonoObject2Value;
};
