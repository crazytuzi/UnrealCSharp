#pragma once

#include "TGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

template <typename T>
class TGarbageCollectionHandleMapping
{
public:
	T& operator[](const TGarbageCollectionHandle<>& InKey);

	const T& operator[](const TGarbageCollectionHandle<>& InKey) const;

	void Empty();

	T& Emplace(TGarbageCollectionHandle<>&& InKey, T&& InValue);

	int32 Remove(const TGarbageCollectionHandle<>& InKey);

	int32 Remove(const MonoObject* InKey);

	T* Find(const MonoObject* InMonoObject);

	T* Find(const TGarbageCollectionHandle<>& InKey);

	bool Contains(const TGarbageCollectionHandle<>& InKey) const;

public:
	TMap<TGarbageCollectionHandle<>, T>& Get();

private:
	TMap<TGarbageCollectionHandle<>, T> GarbageCollectionHandle2T;
};

#include "TGarbageCollectionHandleMapping.inl"
