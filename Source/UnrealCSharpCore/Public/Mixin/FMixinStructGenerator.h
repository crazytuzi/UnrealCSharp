#pragma once

#include "mono/metadata/object.h"

class FMixinStructGenerator
{
private:
	struct FBPVariableDescriptionIndex
	{
		TWeakObjectPtr<UBlueprint> Blueprint;

		int32 Index;
	};

public:
	static void Generator();

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsMixinStruct(MonoClass* InMonoClass);

private:
	static void ReInstance(UScriptStruct* InScriptStruct,
	                       const TArray<FBPVariableDescriptionIndex>& InBPVariableDescriptionIndex);

	static void GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);
};
