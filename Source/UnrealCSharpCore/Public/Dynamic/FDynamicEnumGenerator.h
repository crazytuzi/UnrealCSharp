#pragma once

#include "mono/metadata/object.h"

class FDynamicEnumGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static bool IsDynamicEnum(MonoClass* InMonoClass);

	static MonoClass* GetMonoClass(const FString& InName);
#endif

	static void Generator(MonoClass* InMonoClass);

	static bool UNREALCSHARPCORE_API IsDynamicEnum(const UEnum* InEnum);

private:
	static void BeginGenerator(const UEnum* InEnum);

	static void ProcessGenerator(MonoClass* InMonoClass, UEnum* InEnum);

	static void EndGenerator(UEnum* InEnum);

	static void GeneratorEnum(const FString& InName, UEnum* InEnum,
	                          const TFunction<void(UEnum*)>& InProcessGenerator);

	static UEnum* GeneratorEnum(UPackage* InOuter, const FString& InName);

	static UEnum* GeneratorEnum(UPackage* InOuter, const FString& InName,
	                            const TFunction<void(UEnum*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UEnum* InEnum);

	static void GeneratorMetaData(MonoClass* InMonoClass, UEnum* InEnum);
#endif

	static void GeneratorEnumerator(MonoClass* InMonoClass, UEnum* InEnum);

	static TMap<FString, UEnum*> DynamicEnumMap;

	static TSet<UEnum*> DynamicEnumSet;
};
