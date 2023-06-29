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

	Value& Emplace(Key&& InKey, T&& InValue)
	{
		return GarbageCollectionHandle2T.Emplace(Forward<Key>(InKey), Forward<T>(InValue));
	}

	int32 Remove(const Key& InKey)
	{
		return GarbageCollectionHandle2T.Remove(InKey);
	}

	int32 Remove(const MonoObject* InKey)
	{
		for (const auto& Pair : GarbageCollectionHandle2T)
		{
			if (Pair.Key == InKey)
			{
				return GarbageCollectionHandle2T.Remove(Pair.Key);
			}
		}

		return 0;
	}

	Value* Find(const MonoObject* InMonoObject)
	{
		for (auto& Pair : GarbageCollectionHandle2T)
		{
			if (Pair.Key == InMonoObject)
			{
				return &Pair.Value;
			}
		}

		return nullptr;
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
