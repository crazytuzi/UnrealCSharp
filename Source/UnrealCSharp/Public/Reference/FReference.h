#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"

class UNREALCSHARP_API FReference
{
public:
	explicit FReference(const FGarbageCollectionHandle& InGarbageCollectionHandle):
		GarbageCollectionHandle(InGarbageCollectionHandle)
	{
	}

	virtual ~FReference()
	{
		FGarbageCollectionHandle::Free<true>(GarbageCollectionHandle);
	}

public:
	explicit operator FGarbageCollectionHandle() const
	{
		return GarbageCollectionHandle;
	}

protected:
	FGarbageCollectionHandle GarbageCollectionHandle;
};
