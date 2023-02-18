#pragma once

#include "CoreMinimal.h"

class FSolutionGenerator
{
public:
	static GENERATOR_API void Generator();

private:
	static void CopyTemplate(const FString& Dest, const FString& Src);
};
