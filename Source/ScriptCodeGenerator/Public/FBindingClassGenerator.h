#pragma once

#include "Binding/Class/FBindingClass.h"

class FBindingClassGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

private:
	static void Generator(const FBindingClass* InClass);

	static void GeneratorPartial(const FBindingClass* InClass);

	static void GeneratorImplementation(const FBindingClass* InClass);
};
