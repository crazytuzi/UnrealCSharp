#pragma once

#include "FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

template <typename T>
class TGarbageCollectionHandleMapping
{
public:
	T& operator[](const FGarbageCollectionHandle& InKey);

	const T& operator[](const FGarbageCollectionHandle& InKey) const;

	void Empty();

	T& Emplace(FGarbageCollectionHandle&& InKey, T&& InValue);

	int32 Remove(const FGarbageCollectionHandle& InKey);

	int32 Remove(const MonoObject* InKey);

	T* Find(const MonoObject* InMonoObject);

	T* Find(const FGarbageCollectionHandle& InKey);

	bool Contains(const FGarbageCollectionHandle& InKey) const;

public:
	TMap<FGarbageCollectionHandle, T>& Get();

private:
	TMap<FGarbageCollectionHandle, T> GarbageCollectionHandle2T;
};

#include "TGarbageCollectionHandleMapping.inl"
