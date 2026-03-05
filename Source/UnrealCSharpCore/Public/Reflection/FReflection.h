#pragma once

class FClassReflection;

class FReflection
{
public:
	explicit FReflection(const FString& InName = {},
	                     const TSet<FClassReflection*>& InAttributes = {},
	                     const TMap<FClassReflection*, TArray<FString>>& InAttributeValues = {});

public:
	const FString& GetName() const;

	bool HasAttribute(const FClassReflection* InAttribute) const;

	FString GetAttributeValue(const FClassReflection* InAttribute, int32 InIndex = 0) const;

protected:
	FString Name;

	TSet<FClassReflection*> Attributes;

	TMap<FClassReflection*, TArray<FString>> AttributeValues;
};
