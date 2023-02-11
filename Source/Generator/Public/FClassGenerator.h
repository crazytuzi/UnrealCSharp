#pragma once

#include "CoreMinimal.h"

class FClassGenerator
{
public:
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(const UClass* InClass);

private:
	static bool GeneratorFunctionDefaultParam(const TArray<int32>& FunctionOutParamIndex);

	static FString GetFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GetCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GetBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);
};
