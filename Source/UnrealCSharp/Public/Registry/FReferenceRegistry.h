#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"

class FReferenceRegistry
{
public:
	FReferenceRegistry() = default;

	~FReferenceRegistry();

public:
	bool AddReference(const FGarbageCollectionHandle& InOwner, class FReference* InReference);

	bool RemoveReference(const FGarbageCollectionHandle& InOwner);

private:
	TGarbageCollectionHandleMapping<TSet<class FReference*>> ReferenceRelationship;
};
