#pragma once

#include "CoreMinimal.h"

class FClassGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

	static void Generator(const UClass* InClass);

private:
	static bool GeneratorFunctionDefaultParam(const TArray<int32>& InFunctionOutParamIndex,
	                                          const TArray<int32>& InFunctionRefParamIndex);

	static bool HasFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static bool HasCppFunctionDefaultParam(const UFunction* InFunction, const FProperty* InProperty);

	static bool HasBlueprintFunctionDefaultParam(const UFunction* InFunction, const FProperty* InProperty);

	static FString GetFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GetCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GetBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GeneratorFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GeneratorCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GeneratorBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GeneratorFunctionDefaultParam(FProperty* InProperty, const FString& InMetaData);
};
