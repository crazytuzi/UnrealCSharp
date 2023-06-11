#pragma once

#include "Binding/FBindingClass.h"

class FBindingGenerator
{
public:
	static GENERATOR_API void Generator();

private:
	static void Generator(const FBindingClass& InClass);

	static void GeneratorPartial(const FBindingClass& InClass);

	static void GeneratorImplementation(const FBindingClass& InClass);
};
