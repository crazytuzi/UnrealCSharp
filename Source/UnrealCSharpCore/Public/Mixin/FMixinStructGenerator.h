#pragma once

#include "mono/metadata/object.h"

class FMixinStructGenerator
{
public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsMixinStruct(MonoClass* InMonoClass);

private:
#if WITH_EDITOR
	static void ReInstance(UScriptStruct* InScriptStruct, const TArray<UBlueprint*>& InBlueprints);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);
};
