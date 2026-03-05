#pragma once

#include "Reflection/FClassReflection.h"

class FDynamicEnumGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(FClassReflection* InClassReflection);

	static bool IsDynamicEnum(const UEnum* InEnum);

	static FString GetNameSpace(const UEnum* InEnum);

private:
	static void BeginGenerator(const UEnum* InEnum);

	static void ProcessGenerator(FClassReflection* InClassReflection, UEnum* InEnum);

	static void EndGenerator(UEnum* InEnum);

	static void GeneratorEnum(const FString& InNameSpace, const FString& InName, UEnum* InEnum,
	                          const TFunction<void(UEnum*)>& InProcessGenerator);

	static UEnum* GeneratorEnum(UPackage* InOuter, const FString& InNameSpace, const FString& InName);

	static UEnum* GeneratorEnum(UPackage* InOuter, const FString& InNameSpace, const FString& InName,
	                            const TFunction<void(UEnum*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UEnum* InEnum);
#endif

	static void GeneratorEnumerator(const FClassReflection* InClassReflection, UEnum* InEnum);

private:
	static TMap<UEnum*, FString> NamespaceMap;

	static TMap<FString, UEnum*> DynamicEnumMap;

	static TSet<UEnum*> DynamicEnumSet;
};
