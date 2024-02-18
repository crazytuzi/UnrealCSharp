#pragma once

#include "Dynamic/CSharpClass.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"
#include "Template/TFunctionPointer.inl"
#include "mono/metadata/object.h"

inline uint32 GetTypeHash(const UClass::ClassConstructorType& InClassConstructor)
{
	return GetTypeHash(TFunctionPointer(InClassConstructor).Value.Pointer);
}

class FDynamicClassGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static void OnPrePIEEnded();
#endif

	static void Generator(MonoClass* InMonoClass);

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
	static UNREALCSHARPCORE_API TSet<UClass::ClassConstructorType> ClassConstructorSet;

private:
	static TMap<FString, UClass*> DynamicClasses;
};
