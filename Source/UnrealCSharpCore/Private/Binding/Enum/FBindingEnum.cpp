#include "Binding/Enum/FBindingEnum.h"

TMap<FString, FBindingEnum> FBindingEnum::Enums;

FBindingEnum::FBindingEnum(const FString& InEnum, const FString& InUnderlyingType, FTypeInfo* InTypeInfo):
	Enum(InEnum),
	UnderlyingType(InUnderlyingType),
	TypeInfo(InTypeInfo)
{
}

FBindingEnum* FBindingEnum::GetEnum(const FString& InEnum, const FString& InUnderlyingType, FTypeInfo* InTypeInfo)
{
	if (!Enums.Contains(InEnum))
	{
		Enums.Add(InEnum, {InEnum, InUnderlyingType, InTypeInfo});
	}

	return Enums.Find(InEnum);
}

const TMap<FString, FBindingEnum>& FBindingEnum::GetEnums()
{
	return Enums;
}

const FString& FBindingEnum::GetEnum() const
{
	return Enum;
}

const FString& FBindingEnum::GetUnderlyingType() const
{
	return UnderlyingType;
}

const FBindingTypeInfo& FBindingEnum::GetTypeInfo() const
{
	return TypeInfo;
}

const TMap<FString, int64>& FBindingEnum::GetEnumerators() const
{
	return Enumerators;
}

void FBindingEnum::BindingEnumerator(const FString& InKey, const int64 InEnumerator)
{
	Enumerators.Add(InKey, InEnumerator);
}
