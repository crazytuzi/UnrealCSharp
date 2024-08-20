#include "Binding/Enum/FBindingEnum.h"

FBindingEnum::FBindingEnum(const FString& InEnum,
                           const FString& InUnderlyingType,
                           const bool InIsProjectEnum,
                           const FBindingTypeInfo& InTypeInfo,
                           const TMap<FString, int64>& InEnumerators):
	Enum(InEnum),
	UnderlyingType(InUnderlyingType),
	bIsProjectEnum(InIsProjectEnum),
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

bool FBindingEnum::IsProjectEnum() const
{
	return bIsProjectEnum;
}

const FBindingTypeInfo& FBindingEnum::GetTypeInfo() const
{
	return TypeInfo;
}

const TMap<FString, int64>& FBindingEnum::GetEnumerators() const
{
	return Enumerators;
}
