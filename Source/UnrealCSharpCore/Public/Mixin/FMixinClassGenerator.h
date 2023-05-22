#pragma once

#include "mono/metadata/object.h"

class FMixinClassGenerator
{
public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass);

private:
	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);
};
