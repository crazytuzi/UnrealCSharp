#pragma once

#include "Template/TFunctionPointer.inl"
#include "EDynamicClassGeneratorType.h"
#include "mono/metadata/object.h"

inline uint32 GetTypeHash(const UClass::ClassConstructorType& InClassConstructor)
{
	return GetTypeHash(TFunctionPointer(InClassConstructor).Value.Pointer);
}

class FDynamicClassGenerator
{
public:
	struct FDefaultSubObjectInfo
	{
		const FObjectProperty* Property;

		bool bIsRootComponent = false;

		FString Parent;

		FString Socket;
	};

public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static bool IsDynamicClass(MonoClass* InMonoClass);

	static void OnPrePIEEnded(const bool bIsSimulating);

	static UNREALCSHARPCORE_API const TSet<UClass*>& GetDynamicClasses();
#endif

	static void Generator(MonoClass* InMonoClass, EDynamicClassGeneratorType InDynamicClassGeneratorType);

	static UNREALCSHARPCORE_API bool IsDynamicClass(const UClass* InClass);

	static UNREALCSHARPCORE_API bool IsDynamicBlueprintGeneratedClass(const UField* InField);

	static bool IsDynamicBlueprintGeneratedClass(const UBlueprintGeneratedClass* InClass);

	static bool IsDynamicBlueprintGeneratedSubClass(const UBlueprintGeneratedClass* InClass);

	static UNREALCSHARPCORE_API UClass* GetDynamicClass(MonoClass* InMonoClass);

	static FString GetNameSpace(const UClass* InClass);

private:
	static void BeginGenerator(UClass* InClass, UClass* InParentClass);

	static void BeginGenerator(UBlueprintGeneratedClass* InClass, UClass* InParentClass);

	static void ProcessGenerator(MonoClass* InMonoClass, UClass* InClass);

	static void EndGenerator(UClass* InClass);

	template <typename T>
	static auto GeneratorClass(const FString& InNameSpace, const FString& InName, T InClass, UClass* InParentClass,
	                           const TFunction<void(UClass*)>& InProcessGenerator)
	{
		NamespaceMap.Add(InClass, InNameSpace);

		DynamicClassMap.Add(InName, InClass);

		DynamicClassSet.Add(InClass);

		BeginGenerator(InClass, InParentClass);

		InProcessGenerator(InClass);

		EndGenerator(InClass);
	}

	static UClass* GeneratorClass(UPackage* InOuter, const FString& InNameSpace, const FString& InName,
	                              UClass* InParentClass);

	static UClass* GeneratorClass(UPackage* InOuter, const FString& InNameSpace, const FString& InName,
	                              UClass* InParentClass, const TFunction<void(UClass*)>& InProcessGenerator);

	static UBlueprintGeneratedClass* GeneratorBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InNameSpace, const FString& InName, UClass* InParentClass);

	static UBlueprintGeneratedClass* GeneratorBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InNameSpace, const FString& InName, UClass* InParentClass,
		const TFunction<void(UClass*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UClass* InOldClass, UClass* InNewClass);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorInterface(MonoClass* InMonoClass, UClass* InClass);

	static void ClassConstructor(const FObjectInitializer& InObjectInitializer);

	static bool IsDynamicBlueprintGeneratedClass(const FString& InName);

	static void NewComponentTemplate(class USCS_Node* InNode, UObject* InOuter, UClass* InClass, const FName& InName);

#if WITH_EDITOR
	static void RemoveComponentTemplate(const UBlueprintGeneratedClass* InBlueprintGeneratedClass,
	                                    const USCS_Node* InNode);
#endif

	static USCS_Node* NewNode(USimpleConstructionScript* InSimpleConstructionScript, UObject* InOuter, UClass* InClass,
	                          const FName& InName);

public:
	static UNREALCSHARPCORE_API TSet<UClass::ClassConstructorType> ClassConstructorSet;

private:
	static TMap<UClass*, FString> NamespaceMap;

	static TMap<UClass*, TArray<FDefaultSubObjectInfo>> DefaultSubObjectInfoMap;

	static TMap<FString, UClass*> DynamicClassMap;

	static TSet<UClass*> DynamicClassSet;
};
