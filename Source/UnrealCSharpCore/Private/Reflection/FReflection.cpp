#include "Reflection/FReflection.h"
#include "Reflection/FClassReflection.h"

FReflection::FReflection(const FString& InName,
                         const TSet<FClassReflection*>& InAttributes,
                         const TMap<FClassReflection*, TArray<FString>>& InAttributeValues):
	Name(InName),
	Attributes(InAttributes),
	AttributeValues(InAttributeValues)
{
}

const FString& FReflection::GetName() const
{
	return Name;
}

bool FReflection::HasAttribute(const FClassReflection* InAttribute) const
{
	return Attributes.Contains(InAttribute);
}

FString FReflection::GetAttributeValue(const FClassReflection* InAttribute, const int32 InIndex) const
{
	const auto FoundAttributeAttributeValue = AttributeValues.Find(InAttribute);

	return FoundAttributeAttributeValue != nullptr
		       ? (FoundAttributeAttributeValue->IsValidIndex(InIndex)
			          ? (*FoundAttributeAttributeValue)[InIndex]
			          : FString())
		       : FString();
}
