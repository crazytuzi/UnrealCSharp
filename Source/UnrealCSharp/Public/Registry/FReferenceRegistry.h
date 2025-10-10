#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"

class UNREALCSHARP_API FReferenceRegistry : FGCObject
{
public:
	FReferenceRegistry() = default;

	virtual ~FReferenceRegistry() override;

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override;

public:
	bool AddReference(const FGarbageCollectionHandle& InOwner, class FReference* InReference);

	bool RemoveReference(const FGarbageCollectionHandle& InOwner);

	bool AddReference(UObject* InObject);

	bool RemoveReference(UObject* InObject);

private:
	TGarbageCollectionHandleMapping<TSet<class FReference*>> ReferenceRelationship;

	TArray<TObjectPtr<UObject>> ObjectArray;
};
