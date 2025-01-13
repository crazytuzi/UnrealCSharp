#pragma once

#include "Dynamic/DynamicScriptStruct.h"
#include "mono/metadata/object.h"

class FDynamicStructGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();

	static bool IsDynamicStruct(MonoClass* InMonoClass);
#endif

	static void Generator(MonoClass* InMonoClass);

	static bool IsDynamicStruct(const UScriptStruct* InScriptStruct);

	static FString GetNameSpace(const UScriptStruct* InScriptStruct);

private:
	static void BeginGenerator(UDynamicScriptStruct* InScriptStruct, UScriptStruct* InParentScriptStruct);

	static void ProcessGenerator(MonoClass* InMonoClass, UDynamicScriptStruct* InScriptStruct);

	static void EndGenerator(UDynamicScriptStruct* InScriptStruct);

	static void GeneratorStruct(const FString& InNameSpace, const FString& InName,
	                            UDynamicScriptStruct* InScriptStruct, UScriptStruct* InParentScriptStruct,
	                            const TFunction<void(UDynamicScriptStruct*)>& InProcessGenerator);

	static UDynamicScriptStruct* GeneratorStruct(UPackage* InOuter, const FString& InNameSpace,
	                                             const FString& InName, UScriptStruct* InParentScriptStruct);

	static UDynamicScriptStruct* GeneratorStruct(UPackage* InOuter, const FString& InNameSpace,
	                                             const FString& InName, UScriptStruct* InParentScriptStruct,
	                                             const TFunction<void(UDynamicScriptStruct*)>& InProcessGenerator);

#if WITH_EDITOR
	static void ReInstance(UDynamicScriptStruct* InOldScriptStruct, UDynamicScriptStruct* InNewScriptStruct);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UDynamicScriptStruct* InScriptStruct);

private:
	static TMap<UDynamicScriptStruct*, FString> NamespaceMap;

	static TMap<FString, UDynamicScriptStruct*> DynamicStructMap;

	static TSet<UDynamicScriptStruct*> DynamicStructSet;
};
