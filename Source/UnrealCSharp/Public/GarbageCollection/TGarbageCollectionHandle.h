#pragma once

#include "mono/metadata/object-forward.h"

template <typename T = uint32>
class TGarbageCollectionHandle
{
public:
	TGarbageCollectionHandle();

	TGarbageCollectionHandle(const T& InHandle);

	operator T() const;

	operator MonoObject*() const;

	bool operator==(const TGarbageCollectionHandle& Other) const;

	bool operator!=(const TGarbageCollectionHandle& Other) const;

private:
	T Handle;
};

#include "TGarbageCollectionHandle.inl"
