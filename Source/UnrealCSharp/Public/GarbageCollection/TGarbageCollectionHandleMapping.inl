#pragma once

#include "FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

template <typename T>
class TGarbageCollectionHandleMapping
{
public:
	T& operator[](const FGarbageCollectionHandle& InKey)
	{
		return GarbageCollectionHandle2T[InKey];
	}

	const T& operator[](const FGarbageCollectionHandle& InKey) const
	{
		return GarbageCollectionHandle2T[InKey];
	}

	void Empty()
	{
		GarbageCollectionHandle2T.Empty();
	}

	T& Emplace(FGarbageCollectionHandle&& InKey, T&& InValue)
	{
		return GarbageCollectionHandle2T.Emplace(Forward<FGarbageCollectionHandle>(InKey), Forward<T>(InValue));
	}

	int32 Remove(const FGarbageCollectionHandle& InKey)
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

	T* Find(const MonoObject* InMonoObject)
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

	T* Find(const FGarbageCollectionHandle& InKey)
	{
		return GarbageCollectionHandle2T.Find(InKey);
	}

	bool Contains(const FGarbageCollectionHandle& InKey) const
	{
		return GarbageCollectionHandle2T.Contains(InKey);
	}

public:
	TMap<FGarbageCollectionHandle, T>& Get()
	{
		return GarbageCollectionHandle2T;
	}

private:
	TMap<FGarbageCollectionHandle, T> GarbageCollectionHandle2T;
};
