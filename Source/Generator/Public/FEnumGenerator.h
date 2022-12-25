#pragma once

#include "CoreMinimal.h"

class FEnumGenerator
{
public:
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(const UEnum* InEnum);
};
