#include "Registry/FReferenceRegistry.h"
#include "Domain/FDomain.h"
#include "CoreMacro/Macro.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reference/FReference.h"

FReferenceRegistry::~FReferenceRegistry()
{
	TArray<FReference*> References;

	for (const auto& [PLACEHOLDER, Value] : ReferenceRelationship.Get())
	{
		for (const auto& Reference : Value)
		{
			References.Add(Reference);
		}
	}

	ReferenceRelationship.Empty();

	for (const auto Reference : References)
	{
		delete Reference;
	}

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

bool FReferenceRegistry::AddReference(const IManagedHandle InOwner, FReference* InReference)
{
	if (!ReferenceRelationship.Contains(InOwner))
	{
		ReferenceRelationship.Add(InOwner, {});
	}

	ReferenceRelationship[InOwner].Emplace(InReference);

	return true;
}

bool FReferenceRegistry::RemoveReference(const IManagedHandle InOwner)
{
	TArray<FReference*> References;

	if (const auto FoundReferences = ReferenceRelationship.Find(InOwner))
	{
		References.Reserve(FoundReferences->Num());

		for (const auto& Reference : *FoundReferences)
		{
			References.Add(Reference);
		}

		ReferenceRelationship.Remove(InOwner);
	}

	for (const auto Reference : References)
	{
		delete Reference;
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
