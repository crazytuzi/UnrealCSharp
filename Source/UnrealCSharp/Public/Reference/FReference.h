#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"

class FReference
{
public:
	explicit FReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	virtual ~FReference();

public:
	explicit operator FGarbageCollectionHandle() const;

protected:
	FGarbageCollectionHandle GarbageCollectionHandle;
};
