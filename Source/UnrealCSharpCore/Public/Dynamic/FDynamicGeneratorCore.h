#pragma once

#include "mono/metadata/details/reflection-types.h"

class FDynamicGeneratorCore
{
public:
	static UPackage* GetOuter();

	static FString GetClassNameSpace();

	static void SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetFunctionFlags(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

#if WITH_EDITOR
	static void SetMetaData(UClass* InClass, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UScriptStruct* InScriptStruct, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UEnum* InEnum, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static void SetMetaData(UFunction* InFunction, MonoCustomAttrInfo* InMonoCustomAttrInfo);

	static TArray<FString> GetDynamic(const FString& InFile, const FString& InField);

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

private:
	static TArray<FString> ClassMetaDataAttrs;

	static TArray<FString> StructMetaDataAttrs;

	static TArray<FString> EnumMetaDataAttrs;

	static TArray<FString> PropertyMetaDataAttrs;

	static TArray<FString> FunctionMetaDataAttrs;
};
