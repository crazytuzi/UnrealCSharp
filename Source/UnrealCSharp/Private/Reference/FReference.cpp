#include "Reference/FReference.h"

FReference::FReference(const TGarbageCollectionHandle<>& InGarbageCollectionHandle):
	GarbageCollectionHandle(InGarbageCollectionHandle)
{
}

FReference::~FReference()
{
	FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(GarbageCollectionHandle);
}

FReference::operator TGarbageCollectionHandle<>() const
{
	return GarbageCollectionHandle;
}
