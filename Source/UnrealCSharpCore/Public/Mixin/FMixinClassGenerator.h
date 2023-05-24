#pragma once

#include "mono/metadata/object.h"

class FMixinClassGenerator
{
public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsMixinClass(MonoClass* InMonoClass);

private:
#if WITH_EDITOR
	static void ReInstance(UClass* InClass);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);
};
