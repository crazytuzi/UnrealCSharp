#include "Reference/FReference.h"

FReference::FReference(const FGarbageCollectionHandle& InGarbageCollectionHandle):
	GarbageCollectionHandle(InGarbageCollectionHandle)
{
}

FReference::~FReference()
{
	FGarbageCollectionHandle::Free<true>(GarbageCollectionHandle);
}

FReference::operator FGarbageCollectionHandle() const
{
	return GarbageCollectionHandle;
}
