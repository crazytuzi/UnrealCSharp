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
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(const UEnum* InEnum);

	static void AddEnumUnderlyingType(const UEnum* InEnum, const FNumericProperty* InNumericProperty);

	// @TODO
	static GENERATOR_API void EmptyEnumUnderlyingType();

private:
	static void GeneratorCollisionChannel();

	static FString GetEnumUnderlyingTypeName(const UEnum* InEnum);

private:
	static TMap<const UEnum*, EEnumUnderlyingType> EnumUnderlyingType;
};
