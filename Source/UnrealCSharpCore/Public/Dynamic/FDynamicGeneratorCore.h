#pragma once

#if WITH_EDITOR
#include "EDynamicType.h"
#endif
#include "FDynamicDependencyGraph.h"
#include "mono/metadata/details/reflection-types.h"
#include "Reflection/FClassReflection.h"

class FDynamicGeneratorCore
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

	static void GeneratorField(MonoReflectionType* InMonoReflectionType, FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorField(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoReflectionType* InMonoReflectionType,
	                           FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorProperty(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorFunction(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode);

	static void GeneratorInterface(MonoClass* InMonoClass, FDynamicDependencyGraph::FNode& OutNode);

	static bool ClassHasAttr(MonoClass* InMonoClass, const FString& InAttributeName);

	static void Generator(MonoClass* InAttributeMonoClass, const TFunction<void(MonoClass*)>& InGenerator);

	static UPackage* GetOuter();

	static FString GetClassNameSpace();

	static void SetFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFlags(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFlags(UScriptStruct* InScriptStruct, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFlags(UEnum* InEnum, MonoCustomAttrInfo* InMonoCustomAttrInfo);

#if WITH_EDITOR
	static void SetMetaData(FField* InField, const FString& InAttribute, const FString& InValue);

	static void SetMetaData(UField* InField, const FString& InAttribute, const FString& InValue);

	static void SetMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UScriptStruct* InScriptStruct, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UEnum* InEnum, MonoCustomAttrInfo* InMonoCustomAttrInfo);

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

	static bool AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);
	
	static bool AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass);

	static MonoObject* AttrsGetAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);
	
	static MonoObject* AttrsGetAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass);

	static FString AttrGetValue(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName);

	static FString AttrGetValue(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass);
	
	static void GeneratorProperty(MonoClass* InMonoClass, UField* InField,
	                              const TFunction<void(const MonoProperty*, MonoCustomAttrInfo*, const FProperty*)>&
	                              InGenerator);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass,
	                              const TFunction<void(const UFunction* InFunction)>& InGenerator);

	static MonoClass* UInterfaceToIInterface(MonoClass* InMonoClass);

	static MonoClass* IInterfaceToUInterface(MonoClass* InMonoClass);

#if WITH_EDITOR
	static EDynamicType GetDynamicType(const FString& InName);
	
	static const TArray<FClassReflection*>& GetClassMetaDataAttrs();

	static const TArray<FClassReflection*>& GetStructMetaDataAttrs();

	static const TArray<FClassReflection*>& GetEnumMetaDataAttrs();

	static const TArray<FClassReflection*>& GetInterfaceMetaDataAttrs();

	static const TArray<FClassReflection*>& GetPropertyMetaDataAttrs();

	static const TArray<FClassReflection*>& GetFunctionMetaDataAttrs();
#endif

private:
#if WITH_EDITOR
	static TMap<FString, TArray<FString>> DynamicMap;
#endif
};
