#pragma once

#include "Dynamic/CSharpClass.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"
#include "mono/metadata/object.h"

class FDynamicClassGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsDynamicClass(MonoClass* InMonoClass);

	static UNREALCSHARPCORE_API UClass* GetDynamicClass(MonoClass* InMonoClass);

private:
	static void BeginGenerator(UClass* InClass, UClass* InParentClass);

	static void BeginGenerator(UCSharpBlueprintGeneratedClass* InClass, UClass* InParentClass);

	static void EndGenerator(UClass* InClass);

	static UCSharpClass* GeneratorCSharpClass(
		UPackage* InOuter, const FString& InName, UClass* InParentClass);

	static UCSharpBlueprintGeneratedClass* GeneratorCSharpBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InName, UClass* InParentClass);

#if WITH_EDITOR
	static void ReInstance(UClass* InOldClass, UClass* InNewClass);

	static void GeneratorMetaData(MonoClass* InMonoClass, UClass* InClass);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);

	static void ClassConstructor(const FObjectInitializer& InObjectInitializer);

public:
	static UNREALCSHARPCORE_API TSet<void*> ClassConstructorSet;

private:
	static TMap<FString, UClass*> DynamicClass;
};
