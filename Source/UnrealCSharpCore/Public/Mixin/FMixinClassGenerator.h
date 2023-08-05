#pragma once

#include "Mixin/CSharpGeneratedClass.h"
#include "Mixin/CSharpBlueprintGeneratedClass.h"
#include "mono/metadata/object.h"

class FMixinClassGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsMixinClass(MonoClass* InMonoClass);

private:
	static void BeginGenerator(UClass* InClass, UClass* InParentClass);

	static void EndGenerator(UClass* InClass);

	static UCSharpGeneratedClass* GeneratorCSharpGeneratedClass(UPackage* InOuter, const FString& InName);

	static UCSharpBlueprintGeneratedClass* GeneratorCSharpBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InName);

#if WITH_EDITOR
	static void ReInstance(UClass* InClass);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);
};
