#pragma once

#include "Binding/Enum/FBindingEnum.h"

class FBindingEnumGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

private:
	static void Generator(const FBindingEnum* InEnum);
};
