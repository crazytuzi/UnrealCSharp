#pragma once

#include "CSharpScriptStruct.h"
#include "mono/metadata/object.h"

class FDynamicStructGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsDynamicStruct(MonoClass* InMonoClass);

private:
	static void BeginGenerator(UScriptStruct* InScriptStruct);

	static void EndGenerator(UScriptStruct* InScriptStruct);

	static UCSharpScriptStruct* GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName);

#if WITH_EDITOR
	static void ReInstance(UScriptStruct* InScriptStruct);

	static void GeneratorMetaData(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);

	static TMap<FString, UCSharpScriptStruct*> DynamicStruct;
};
