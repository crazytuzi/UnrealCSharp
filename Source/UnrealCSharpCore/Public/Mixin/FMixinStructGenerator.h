#pragma once

#include "mono/metadata/object.h"

class FMixinStructGenerator
{
public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass);

private:
	static void GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);
};
