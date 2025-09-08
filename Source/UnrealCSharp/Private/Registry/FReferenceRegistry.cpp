#include "Registry/FReferenceRegistry.h"
#include "CoreMacro/Macro.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reference/FReference.h"

FReferenceRegistry::~FReferenceRegistry()
{
	for (const auto& [PLACEHOLDER, Value] : ReferenceRelationship.Get())
	{
		for (const auto& Reference : Value)
		{
			auto GarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(*Reference);

			FGarbageCollectionHandle::Free<true>(GarbageCollectionHandle);

			delete Reference;
		}
	}

	ReferenceRelationship.Empty();

	ObjectArray.Empty();
}

void FReferenceRegistry::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObjects(ObjectArray);
}

FString FReferenceRegistry::GetReferencerName() const
{
	return TEXT("FReferenceRegistry");
}

bool FReferenceRegistry::AddReference(const FGarbageCollectionHandle& InOwner, FReference* InReference)
{
	if (!ReferenceRelationship.Contains(InOwner))
	{
		ReferenceRelationship.Add(InOwner, {});
	}

	ReferenceRelationship[InOwner].Emplace(InReference);

	return true;
}

bool FReferenceRegistry::RemoveReference(const FGarbageCollectionHandle& InOwner)
{
	if (const auto FoundReferences = ReferenceRelationship.Find(InOwner))
	{
		for (const auto& Reference : *FoundReferences)
		{
			delete Reference;
		}

		ReferenceRelationship.Remove(InOwner);
	}

	return true;
}

bool FReferenceRegistry::AddReference(UObject* InObject)
{
	if (InObject != nullptr)
	{
		ObjectArray.AddUnique(InObject);

		return true;
	}

	return false;
}

bool FReferenceRegistry::RemoveReference(UObject* InObject)
{
	if (InObject != nullptr)
	{
		ObjectArray.Remove(InObject);

		return true;
	}

	return false;
}
