#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.h"

class FReferenceRegistry
{
public:
	FReferenceRegistry() = default;

	~FReferenceRegistry();

public:
	bool AddReference(const TGarbageCollectionHandle<>& InOwner, class FReference* InReference);

	bool RemoveReference(const TGarbageCollectionHandle<>& InOwner);

private:
	TGarbageCollectionHandleMapping<TSet<class FReference*>> ReferenceRelationship;
};
