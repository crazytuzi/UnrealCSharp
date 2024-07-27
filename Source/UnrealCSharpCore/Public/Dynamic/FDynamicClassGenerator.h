#pragma once

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

	static bool IsDynamicClass(MonoClass* InMonoClass);

	static MonoClass* GetMonoClass(const FString& InName);

	static void OnPrePIEEnded();
#endif

	static void Generator(MonoClass* InMonoClass);

	static bool UNREALCSHARPCORE_API IsDynamicClass(const UClass* InClass);

	static bool IsDynamicBlueprintGeneratedClass(const UField* InField);

	static bool IsDynamicBlueprintGeneratedClass(const UBlueprintGeneratedClass* InClass);

	static bool IsDynamicBlueprintGeneratedSubClass(const UBlueprintGeneratedClass* InClass);

	static UNREALCSHARPCORE_API UClass* GetDynamicClass(MonoClass* InMonoClass);

private:
	static void BeginGenerator(UClass* InClass, UClass* InParentClass);

	static void BeginGenerator(UBlueprintGeneratedClass* InClass, UClass* InParentClass);

	static void ProcessGenerator(MonoClass* InMonoClass, UClass* InClass);

	static void EndGenerator(UClass* InClass);

	template <typename T>
	static auto GeneratorClass(const FString& InName, T InClass, UClass* InParentClass,
	                           const TFunction<void(UClass*)>& InProcessGenerator)
	{
		DynamicClassMap.Add(InName, InClass);

		DynamicClassSet.Add(InClass);

		BeginGenerator(InClass, InParentClass);

		InProcessGenerator(InClass);

		EndGenerator(InClass);
	}

	static UClass* GeneratorClass(UPackage* InOuter, const FString& InName, UClass* InParentClass);

	static UClass* GeneratorClass(UPackage* InOuter, const FString& InName, UClass* InParentClass,
	                              const TFunction<void(UClass*)>& InProcessGenerator);

	static UBlueprintGeneratedClass* GeneratorBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InName, UClass* InParentClass);

	static UBlueprintGeneratedClass* GeneratorBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InName, UClass* InParentClass,
		const TFunction<void(UClass*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UClass* InOldClass, UClass* InNewClass);

	static void GeneratorMetaData(MonoClass* InMonoClass, UClass* InClass);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorInterface(MonoClass* InMonoClass, UClass* InClass);

	static void ClassConstructor(const FObjectInitializer& InObjectInitializer);

	static bool IsDynamicBlueprintGeneratedClass(const FString& InName);

public:
	static UNREALCSHARPCORE_API TSet<UClass::ClassConstructorType> ClassConstructorSet;

private:
	static TMap<FString, UClass*> DynamicClassMap;

	static TSet<UClass*> DynamicClassSet;
};
