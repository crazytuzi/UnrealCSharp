#pragma once

#include "mono/metadata/object-forward.h"

template <typename T>
class TMonoObjectMapping
{
public:
	typedef const MonoObject* Key;

	typedef T Value;

public:
	Value& operator[](const Key& InKey)
	{
		return MonoObject2T[InKey];
	}

	const Value& operator[](const Key& InKey) const
	{
		return MonoObject2T[InKey];
	}

	void Empty()
	{
		MonoObject2T.Empty();
	}

	void Add(const Key& InKey, const T& InValue)
	{
		MonoObject2T.Add(InKey, InValue);
	}

	int32 Remove(const Key& InKey)
	{
		return MonoObject2T.Remove(InKey);
	}

	Value* Find(const Key& InKey)
	{
		return MonoObject2T.Find(InKey);
	}

	bool Contains(const Key& InKey) const
	{
		return MonoObject2T.Contains(InKey);
	}

public:
	TMap<Key, Value>& Get()
	{
		return MonoObject2T;
	}

private:
	TMap<Key, Value> MonoObject2T;
};
