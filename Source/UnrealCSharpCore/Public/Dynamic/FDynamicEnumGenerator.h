#pragma once

#include "mono/metadata/object.h"

class FDynamicEnumGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsDynamicEnum(MonoClass* InMonoClass);

	static bool UNREALCSHARPCORE_API IsDynamicEnum(const UEnum* InEnum);

private:
	static UEnum* GeneratorCSharpEnum(UPackage* InOuter, const FString& InName);

#if WITH_EDITOR
	static void ReInstance(UEnum* InEnum);

	static void GeneratorMetaData(MonoClass* InMonoClass, UEnum* InEnum);
#endif

	static void GeneratorEnumerator(MonoClass* InMonoClass, UEnum* InEnum);

	static TMap<FString, UEnum*> DynamicEnumMap;

	static TSet<UEnum*> DynamicEnumSet;
};
