#pragma once

#include "CoreMinimal.h"

class FSolutionGenerator
{
public:
	static GENERATOR_API void Generator();

private:
	static void Compile();

	static void CopyTemplate(const FString& Dest, const FString& Src);

	static void CopyCSProj(const FString& Dest, const FString& Src);
};
