#pragma once

#include "TManagedHandleMapping.inl"

template <typename Key, typename Value = Key>
struct TValueMapping
{
	typedef Key KeyType;

	typedef Value ValueType;

	typedef TManagedHandleMapping<ValueType> FManagedHandle2Value;

	typedef TMap<KeyType, typename FManagedHandle2Value::KeyType> FKey2ManagedHandle;
};
