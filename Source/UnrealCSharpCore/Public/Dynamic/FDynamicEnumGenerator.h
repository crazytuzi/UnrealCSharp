#pragma once

#include "CSharpEnum.h"
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

private:
	static UCSharpEnum* GeneratorCSharpEnum(UPackage* InOuter, const FString& InName);

#if WITH_EDITOR
	static void ReInstance(const TArray<UBlueprint*>& InBlueprints);
#endif

	static void GeneratorEnumerator(MonoClass* InMonoClass, UEnum* InEnum);
};
