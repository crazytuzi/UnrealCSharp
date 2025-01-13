#pragma once

#include "mono/metadata/object.h"

class FDynamicInterfaceGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static bool IsDynamicInterface(MonoClass* InMonoClass);
#endif

	static void Generator(MonoClass* InMonoClass);

	static bool IsDynamicInterface(const UClass* InClass);

	static FString GetNameSpace(const UClass* InClass);

private:
	static void BeginGenerator(UClass* InClass, UClass* InParentClass);

	static void ProcessGenerator(MonoClass* InMonoClass, UClass* InClass);

	static void EndGenerator(UClass* InClass);

	static void GeneratorInterface(const FString& InNameSpace, const FString& InName,
	                               UClass* InClass, UClass* InParentClass,
	                               const TFunction<void(UClass*)>& InProcessGenerator);

	static UClass* GeneratorInterface(UPackage* InOuter, const FString& InNameSpace,
	                                  const FString& InName, UClass* InParentClass);

	static UClass* GeneratorInterface(UPackage* InOuter, const FString& InNameSpace,
	                                  const FString& InName, UClass* InParentClass,
	                                  const TFunction<void(UClass*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UClass* InClass);
#endif

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);

private:
	static TMap<UClass*, FString> NamespaceMap;

	static TMap<FString, UClass*> DynamicInterfaceMap;

	static TSet<UClass*> DynamicInterfaceSet;
};
