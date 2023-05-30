#pragma once

#include "mono/metadata/object-forward.h"

template <typename T>
class TGarbageCollectionHandle
{
public:
	TGarbageCollectionHandle();

	TGarbageCollectionHandle(const T& InHandle);

	operator T() const;

	operator MonoObject*() const;

	bool operator==(const TGarbageCollectionHandle& Other) const;

	bool operator!=(const TGarbageCollectionHandle& Other) const;

	bool IsValid() const;

public:
	static TGarbageCollectionHandle NewRef(MonoObject* InMonoObject, mono_bool bPinned);

	static TGarbageCollectionHandle NewWeakRef(MonoObject* InMonoObject, mono_bool bTrackResurrection);

	static void Free(TGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	T Handle;
};

#include "TGarbageCollectionHandle.inl"
