#pragma once

#include "mono/metadata/details/reflection-types.h"

class FDynamicGeneratorCore
{
public:
#if WITH_EDITOR
	static void BeginCodeAnalysisGenerator();

	static void EndCodeAnalysisGenerator();

	static void CodeAnalysisGenerator(const FString& InName, const TFunction<void(const FString&)>& InGenerator);

	static bool IsDynamic(MonoClass* InMonoClass, const FString& InAttribute);

	static const FString& DynamicReInstanceBaseName();
#endif

	static void Generator(const FString& InAttribute, const TFunction<void(MonoClass*)>& InGenerator);

	static UPackage* GetOuter();

	static FString GetClassNameSpace();

	static void SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

#if WITH_EDITOR
	static void SetMetaData(MonoClass* InMonoClass, const FString& InAttribute,
	                        const TFunction<void(MonoCustomAttrInfo*)>& InSetMetaData);

	static void SetMetaData(MonoClass* InMonoClass, UClass* InClass, const FString& InAttribute);

	static void SetMetaData(MonoClass* InMonoClass, UScriptStruct* InScriptStruct, const FString& InAttribute);

	static void SetMetaData(MonoClass* InMonoClass, UEnum* InEnum, const FString& InAttribute);

	static void SetMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	template <typename T>
	static void IteratorObject(
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

	static void GeneratorProperty(MonoClass* InMonoClass, UField* InField,
	                              const TFunction<void(const FProperty* InProperty)>& InGenerator);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass,
	                              const TFunction<void(const UFunction* InFunction)>& InGenerator);

private:
#if WITH_EDITOR
	static TMap<FString, TArray<FString>> DynamicMap;
#endif

	static TArray<FString> ClassMetaDataAttrs;

	static TArray<FString> StructMetaDataAttrs;

	static TArray<FString> EnumMetaDataAttrs;

	static TArray<FString> InterfaceMetaDataAttrs;

	static TArray<FString> PropertyMetaDataAttrs;

	static TArray<FString> FunctionMetaDataAttrs;
};
