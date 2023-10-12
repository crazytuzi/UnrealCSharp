#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"

class UNREALCSHARP_API FReference
{
public:
	explicit FReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	virtual ~FReference();

public:
	explicit operator FGarbageCollectionHandle() const;

protected:
	FGarbageCollectionHandle GarbageCollectionHandle;
};
