#include "Binding/Enum/FBindingEnum.h"

FBindingEnum::FBindingEnum(const FString& InEnum,
                           const FString& InUnderlyingType,
                           const bool InIsEngineEnum,
                           const FBindingTypeInfo& InTypeInfo,
                           const TMap<FString, int64>& InEnumerators):
	Enum(InEnum),
	UnderlyingType(InUnderlyingType),
	bIsEngineEnum(InIsEngineEnum),
	TypeInfo(InTypeInfo),
	Enumerators(InEnumerators)
{
}

const FString& FBindingEnum::GetEnum() const
{
	return Enum;
}

const FString& FBindingEnum::GetUnderlyingType() const
{
	return UnderlyingType;
}

bool FBindingEnum::IsEngineEnum() const
{
	return bIsEngineEnum;
}

const FBindingTypeInfo& FBindingEnum::GetTypeInfo() const
{
	return TypeInfo;
}

const TMap<FString, int64>& FBindingEnum::GetEnumerators() const
{
	return Enumerators;
}
