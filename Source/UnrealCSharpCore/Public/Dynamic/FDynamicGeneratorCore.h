#pragma once

#if WITH_EDITOR
#include "EDynamicType.h"
#endif
#include "FDynamicDependencyGraph.h"
#include "Reflection/FClassReflection.h"

class UNREALCSHARPCORE_API FDynamicGeneratorCore
{
public:
#if WITH_EDITOR
	static void BeginCodeAnalysisGenerator();

	static void EndCodeAnalysisGenerator();

	static void CodeAnalysisGenerator(const FString& InName,
	                                  const TFunction<void(const FString&, const FString&)>& InGenerator);

	static const FString& DynamicReInstanceBaseName();
#endif

	static void AddNode(const FDynamicDependencyGraph::FNode& InNode);

	static bool IsCompleted(const FString& InName);

	static void Completed(const FString& InName);

	static void OnCompleted(const FString& InName, const TFunction<void()>& InOnCompleted);

	static void Generator();

	static void GeneratorField(FReflection* InReflection, const FClassReflection* InClassReflection,
	                           FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorProperty(const FClassReflection* InClassReflection, FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorFunction(const FClassReflection* InClassReflection, FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorInterface(const FClassReflection* InClassReflection, FDynamicDependencyGraph::FNode& OutNode);

	static void Generator(const FClassReflection* InClassReflection,
	                      const TFunction<void(FClassReflection*)>& InGenerator);

	static UPackage* GetOuter();

	static FString GetClassNameSpace();

	static void SetFlags(FProperty* InProperty, FReflection* InReflection);

	static void SetFlags(UFunction* InFunction, FReflection* InReflection);

	static void SetFlags(FClassReflection* InClassReflection, UClass* InClass);

	static void SetFlags(FClassReflection* InClassReflection, UScriptStruct* InScriptStruct);

	static void SetFlags(FClassReflection* InClassReflection, UEnum* InEnum);

#if WITH_EDITOR
	static void SetMetaData(FField* InField, const FString& InAttribute, const FString& InValue);

	static void SetMetaData(UField* InField, const FString& InAttribute, const FString& InValue);

	static void SetMetaData(FProperty* InProperty, FReflection* InReflection);

	static void SetMetaData(UFunction* InFunction, FReflection* InReflection);

	static void SetMetaData(UClass* InClass, FReflection* InReflection);

	static void SetMetaData(UScriptStruct* InScriptStruct, FReflection* InReflection);

	static void SetMetaData(UEnum* InEnum, FReflection* InReflection);

	template <typename T>
	static auto IteratorObject(
		const TFunction<bool(const TObjectIterator<T>&)>& InPredicate,
		const TUniqueFunction<void(const TObjectIterator<T>&)>& InFunction)
	{
		for (TObjectIterator<T> ObjectIterator; ObjectIterator; ++ObjectIterator)
		{
			if (InPredicate(ObjectIterator))
			{
				InFunction(ObjectIterator);
			}
		}
	}
#endif

	static void GeneratorProperty(const FClassReflection* InClassReflection, UField* InField,
	                              const TFunction<void(FPropertyReflection*, const FProperty*)>& InGenerator);

	static void GeneratorFunction(const FClassReflection* InClassReflection, UClass* InClass,
	                              const TFunction<void(FMethodReflection*, const UFunction* InFunction)>& InGenerator);

	static FClassReflection* UInterfaceToIInterface(const FClassReflection* InClassReflection);

	static FClassReflection* IInterfaceToUInterface(const FClassReflection* InClassReflection);

#if WITH_EDITOR
	static EDynamicType GetDynamicType(const FString& InName);

	static const TArray<FClassReflection*>& GetClassMetaDataAttributes();

	static const TArray<FClassReflection*>& GetStructMetaDataAttributes();

	static const TArray<FClassReflection*>& GetEnumMetaDataAttributes();

	static const TArray<FClassReflection*>& GetInterfaceMetaDataAttributes();

	static const TArray<FClassReflection*>& GetPropertyMetaDataAttributes();

	static const TArray<FClassReflection*>& GetFunctionMetaDataAttributes();
#endif

private:
#if WITH_EDITOR
	static TMap<FString, TArray<FString>> DynamicMap;
#endif
};
