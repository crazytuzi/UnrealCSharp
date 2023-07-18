#pragma once

#include "Binding/TypeInfo/FBindingTypeInfo.h"

class UNREALCSHARPCORE_API FBindingEnum
{
public:
	FBindingEnum(const FString& InEnum, const FString& InFullEnum,
	             const FString& InUnderlyingType, FTypeInfo* InTypeInfo);

	static FBindingEnum* GetEnum(const FString& InEnum, const FString& InFullEnum,
	                             const FString& InUnderlyingType, FTypeInfo* InTypeInfo);

public:
	static const TMap<FString, FBindingEnum>& GetEnums();

public:
	const FString& GetEnum() const;

	const FString& GetFullEnum() const;

	const FString& GetUnderlyingType() const;

	const FBindingTypeInfo& GetTypeInfo() const;

	const TMap<FString, int64>& GetEnumerators() const;

public:
	void BindingEnumerator(const FString& InKey, int64 InEnumerator);

private:
	static TMap<FString, FBindingEnum> Enums;

	FString Enum;

	FString FullEnum;

	FString UnderlyingType;

	FBindingTypeInfo TypeInfo;

	TMap<FString, int64> Enumerators;
};
