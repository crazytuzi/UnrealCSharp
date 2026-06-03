#pragma once

#include "TManagedHandleMapping.inl"

class UNREALCSHARP_API FReferenceRegistry : FGCObject
{
public:
	FReferenceRegistry() = default;

	virtual ~FReferenceRegistry() override;

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override;

public:
	bool AddReference(const IManagedHandle InOwner, class FReference* InReference);

	bool RemoveReference(const IManagedHandle InOwner);

	bool AddReference(UObject* InObject);

	bool RemoveReference(UObject* InObject);

private:
	TManagedHandleMapping<TSet<class FReference*>> ReferenceRelationship;

	TArray<TObjectPtr<UObject>> ObjectArray;
};
