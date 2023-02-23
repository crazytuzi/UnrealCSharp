#include "Reference/FReference.h"

FReference::FReference(const FGarbageCollectionHandle& InGarbageCollectionHandle):
	GarbageCollectionHandle(InGarbageCollectionHandle)
{
}

FReference::~FReference()
{
	FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(GarbageCollectionHandle);
}

FReference::operator FGarbageCollectionHandle() const
{
	return GarbageCollectionHandle;
}
