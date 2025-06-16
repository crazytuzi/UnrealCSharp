#pragma once

#include "CoreMacro/AccessPrivateMacro.h"
#include "Dynamic/DynamicScriptStruct.h"
#if WITH_EDITOR
#include "Kismet2/BlueprintEditorUtils.h"
#include "Editor/Kismet/Internal/Blueprints/BlueprintDependencies.h"
#endif
#include "mono/metadata/object.h"

#if WITH_EDITOR
ACCESS_PRIVATE_STATIC_FUNCTION(FBlueprintEditorUtils, GetNodesForVariable, TArray<UK2Node*>, const FName&, const UBlueprint*, const UStruct*)
ACCESS_PRIVATE_STATIC_FUNCTION(FBlueprintEditorUtils, VerifyUserWantsVariableTypeChanged, bool, const FName&)
#endif

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
