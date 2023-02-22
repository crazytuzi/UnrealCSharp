#include "Registry/FReferenceRegistry.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reference/FReference.h"

FReferenceRegistry::~FReferenceRegistry()
{
	for (const auto& Pair : ReferenceRelationship.Get())
	{
		for (const auto& Reference : Pair.Value)
		{
			FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(
				static_cast<TGarbageCollectionHandle<>>(*Reference));

			delete Reference;
		}
	}

	ReferenceRelationship.Empty();
}

bool FReferenceRegistry::AddReference(const TGarbageCollectionHandle<>& InOwner, FReference* InReference)
{
	if (!ReferenceRelationship.Contains(InOwner))
	{
		ReferenceRelationship.Emplace(CopyTemp(InOwner), {});
	}

	ReferenceRelationship[InOwner].Emplace(InReference);

	return true;
}

bool FReferenceRegistry::RemoveReference(const TGarbageCollectionHandle<>& InOwner)
{
	if (const auto FoundReferences = ReferenceRelationship.Find(InOwner))
	{
		for (const auto& Reference : *FoundReferences)
		{
			FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(
				static_cast<TGarbageCollectionHandle<>>(*Reference));

			delete Reference;
		}

		ReferenceRelationship.Remove(InOwner);
	}

	return true;
}
