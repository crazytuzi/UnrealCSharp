#include "Registry/FReferenceRegistry.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reference/FReference.h"

FReferenceRegistry::~FReferenceRegistry()
{
	for (const auto& Pair : ReferenceRelationship.Get())
	{
		for (const auto& Reference : Pair.Value)
		{
			auto GarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(*Reference);

			FGarbageCollectionHandle::Free(GarbageCollectionHandle);

			delete Reference;
		}
	}

	ReferenceRelationship.Empty();
}

bool FReferenceRegistry::AddReference(const FGarbageCollectionHandle& InOwner, FReference* InReference)
{
	if (!ReferenceRelationship.Contains(InOwner))
	{
		ReferenceRelationship.Emplace(CopyTemp(InOwner), {});
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
