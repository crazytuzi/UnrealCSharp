#pragma once

#include "CoreMinimal.h"

class FClassGenerator
{
public:
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(const UClass* InClass);

private:
	static bool GeneratorFunctionDefaultParam(const TArray<int32>& InFunctionOutParamIndex,
	                                          const TArray<int32>& InFunctionRefParamIndex);

	static bool HasFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static bool HasCppFunctionDefaultParam(const UFunction* InFunction, const FProperty* InProperty);

	static bool HasBlueprintFunctionDefaultParam(const UFunction* InFunction, const FProperty* InProperty);

	static FString GetFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GetCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GetBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty);

	static FString GeneratorFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty,
	                                             const FString& InFunctionTab);

	static FString GeneratorCppFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty,
	                                                const FString& InFunctionTab);

	static FString GeneratorBlueprintFunctionDefaultParam(const UFunction* InFunction, FProperty* InProperty,
	                                                      const FString& InFunctionTab);

	static FString GeneratorFunctionDefaultParam(FProperty* InProperty, const FString& InMetaData,
	                                             const FString& InFunctionTab);

	static TArray<FString> GetOverrideFunctions(const FString& InNameSpace, const FString& InClass);
};
