#pragma once

#include "CoreMinimal.h"

enum class EEnumUnderlyingType
{
	None,
	Int8,
	UInt8,
	Int16,
	UInt16,
	Int,
	UInt32,
	Int64,
	UInt64
};

class FEnumGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

	static void Generator(const UEnum* InEnum);

	static void AddEnumUnderlyingType(const UEnum* InEnum, const FNumericProperty* InNumericProperty);

private:
	static void GeneratorCollisionChannel();

	static FString GetEnumUnderlyingTypeName(const UEnum* InEnum);

private:
	friend class FGeneratorCore;

	static TMap<const UEnum*, EEnumUnderlyingType> EnumUnderlyingType;
};
