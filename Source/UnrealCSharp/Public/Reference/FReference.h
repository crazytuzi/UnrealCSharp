#pragma once

#include "GarbageCollection/TGarbageCollectionHandle.h"

class FReference
{
public:
	explicit FReference(const TGarbageCollectionHandle<>& InGarbageCollectionHandle);

	virtual ~FReference();

public:
	explicit operator TGarbageCollectionHandle<>() const;

protected:
	TGarbageCollectionHandle<> GarbageCollectionHandle;
};
