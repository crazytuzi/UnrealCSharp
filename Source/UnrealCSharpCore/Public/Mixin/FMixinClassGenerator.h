#pragma once

#include "mono/metadata/object.h"

class FMixinClassGenerator
{
public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsMixinClass(MonoClass* InMonoClass);

private:
	static void ReInstance(const UClass* InClass);

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);
};
