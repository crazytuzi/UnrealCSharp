#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "GarbageCollection/TMonoObjectMapping.inl"

template <typename Key, typename Value = Key>
struct TValueMapping
{
	typedef Key KeyType;

	typedef Value ValueType;

	typedef TGarbageCollectionHandleMapping<ValueType> GarbageCollectionHandle2Value;

	typedef TMap<KeyType, typename GarbageCollectionHandle2Value::KeyType> Value2GarbageCollectionHandle;

	typedef TMonoObjectMapping<ValueType> MonoObject2Value;
};
