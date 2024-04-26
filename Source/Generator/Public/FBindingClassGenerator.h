#pragma once

#include "Binding/Class/FBindingClass.h"

class FBindingClassGenerator
{
public:
	static GENERATOR_API void Generator();

private:
	static void Generator(const FBindingClass* InClass);

	static void GeneratorPartial(const FBindingClass* InClass);

	static FString GetFunctionDefaultParam(const FTypeInfo* InTypeInfo, const FString& InDefaultArgument);

	static void GeneratorImplementation(const FBindingClass* InClass);
};
