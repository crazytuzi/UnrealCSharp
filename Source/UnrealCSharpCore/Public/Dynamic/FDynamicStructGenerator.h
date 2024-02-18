#pragma once

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

	static bool UNREALCSHARPCORE_API IsDynamicStruct(const UScriptStruct* InScriptStruct);

private:
	static void BeginGenerator(UScriptStruct* InScriptStruct);

	static void EndGenerator(UScriptStruct* InScriptStruct);

	static UScriptStruct* GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName);

#if WITH_EDITOR
	static void ReInstance(UScriptStruct* InScriptStruct);

	static void GeneratorMetaData(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);

	static TMap<FString, UScriptStruct*> DynamicStructMap;

	static TSet<UScriptStruct*> DynamicStructSet;
};
