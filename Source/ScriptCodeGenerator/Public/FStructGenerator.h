#pragma once

#include "CoreMinimal.h"

class FStructGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

	static void Generator(const UScriptStruct* InScriptStruct);
};
