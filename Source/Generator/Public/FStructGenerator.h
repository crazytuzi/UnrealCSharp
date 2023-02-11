#pragma once

#include "CoreMinimal.h"

class FStructGenerator
{
public:
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(const UScriptStruct* InScriptStruct);
};
