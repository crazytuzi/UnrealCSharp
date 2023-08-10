#pragma once

#include "FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

template <typename T>
class TGarbageCollectionHandleMapping
{
public:
	typedef FGarbageCollectionHandle Key;

	typedef T Value;

public:
	Value& operator[](const Key& InKey)
	{
		return GarbageCollectionHandle2T[InKey];
	}

	const Value& operator[](const Key& InKey) const
	{
		return GarbageCollectionHandle2T[InKey];
	}

	void Empty()
	{
		GarbageCollectionHandle2T.Empty();
	}

	void Add(const Key& InKey, const T& InValue)
	{
		GarbageCollectionHandle2T.Add(InKey, InValue);
	}

	int32 Remove(const Key& InKey)
	{
		return GarbageCollectionHandle2T.Remove(InKey);
	}

	Value* Find(const Key& InKey)
	{
		return GarbageCollectionHandle2T.Find(InKey);
	}

	bool Contains(const Key& InKey) const
	{
		return GarbageCollectionHandle2T.Contains(InKey);
	}

public:
	TMap<Key, Value>& Get()
	{
		return GarbageCollectionHandle2T;
	}

private:
	TMap<Key, Value> GarbageCollectionHandle2T;
};
