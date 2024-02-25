#pragma once

#include "mono/metadata/object.h"

class FDynamicStructGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(MonoClass* InMonoClass);

	static bool IsDynamicStruct(MonoClass* InMonoClass);

	static bool UNREALCSHARPCORE_API IsDynamicStruct(const UScriptStruct* InScriptStruct);

private:
	static void BeginGenerator(UScriptStruct* InScriptStruct, UScriptStruct* InParentScriptStruct);

	static void ProcessGenerator(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);

	static void EndGenerator(UScriptStruct* InScriptStruct);

	static void GeneratorScriptStruct(const FString& InName, UScriptStruct* InScriptStruct,
	                                  UScriptStruct* InParentScriptStruct,
	                                  const TFunction<void(UScriptStruct*)>& InProcessGenerator);

	static UScriptStruct* GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName,
	                                                  UScriptStruct* InParentScriptStruct);

	static UScriptStruct* GeneratorCSharpScriptStruct(UPackage* InOuter, const FString& InName,
	                                                  UScriptStruct* InParentScriptStruct,
	                                                  const TFunction<void(UScriptStruct*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UScriptStruct* InOldScriptStruct, UScriptStruct* InNewScriptStruct);

	static void GeneratorMetaData(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UScriptStruct* InScriptStruct);

	static TMap<FString, UScriptStruct*> DynamicStructMap;

	static TSet<UScriptStruct*> DynamicStructSet;
};
