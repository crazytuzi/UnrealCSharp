#pragma once

#include "mono/metadata/object.h"

class FMixinEnumGenerator
{
public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsMixinEnum(MonoClass* InMonoClass);

private:
#if WITH_EDITOR
	static void ReInstance(const TArray<UBlueprint*>& InBlueprints);
#endif

	static void GeneratorEnumerator(MonoClass* InMonoClass, UEnum* InEnum);
};
