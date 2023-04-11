#include "Reference/FReference.h"

FReference::FReference(const FGarbageCollectionHandle& InGarbageCollectionHandle):
	GarbageCollectionHandle(InGarbageCollectionHandle)
{
}

FReference::~FReference()
{
	FGarbageCollectionHandle::Free(GarbageCollectionHandle);
}

FReference::operator FGarbageCollectionHandle() const
{
	return GarbageCollectionHandle;
}
