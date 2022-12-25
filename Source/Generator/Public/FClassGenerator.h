#pragma once

#include "CoreMinimal.h"

class FClassGenerator
{
public:
	static GENERATOR_API void Generator();

	static GENERATOR_API void Generator(UClass* InClass);

private:
	static FString GetFullInterface(const UStruct* InStruct);
};
