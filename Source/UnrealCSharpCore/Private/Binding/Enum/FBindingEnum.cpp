#include "Binding/Enum/FBindingEnum.h"

TMap<FString, FBindingEnum> FBindingEnum::Enums;

FBindingEnum::FBindingEnum(const FString& InEnum, const FString& InFullEnum, FTypeInfo* InTypeInfo):
	Enum(InEnum),
	FullEnum(InFullEnum),
	TypeInfo(InTypeInfo)
{
}

FBindingEnum* FBindingEnum::GetEnum(const FString& InEnum, const FString& InFullEnum, FTypeInfo* InTypeInfo)
{
	if (!Enums.Contains(InEnum))
	{
		Enums.Add(InEnum, {InEnum, InFullEnum, InTypeInfo});
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

const FString& FBindingEnum::GetFullEnum() const
{
	return FullEnum;
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
