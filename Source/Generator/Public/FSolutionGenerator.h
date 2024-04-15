#pragma once

#include "CoreMinimal.h"

class FSolutionGenerator
{
public:
	static GENERATOR_API void Generator();

private:
	static void CopyTemplate(const FString& Dest, const FString& Src);

	static void CopyTemplate(const FString& Dest, const FString& Src,
	                         const TFunction<void(FString& InResult)>& InCopyTemplate);

	static void CopyCSProj(const FString& Dest, const FString& Src);

	static void CopySolution(const FString& Dest, const FString& Src);
};
