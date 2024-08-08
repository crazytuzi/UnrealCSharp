#pragma once

#include "CoreMinimal.h"

class FSolutionGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

private:
	static void CopyTemplate(const FString& Dest, const FString& Src);

	static void CopyTemplate(const FString& Dest, const FString& Src,
	                         const TArray<TFunction<void(FString& OutResult)>>& InFunction);

	static void ReplacePluginBaseDir(FString& OutResult);

	static void ReplaceImport(FString& OutResult);

	static void ReplaceDefineConstants(FString& OutResult);

	static void ReplaceOutputPath(FString& OutResult);

	static void ReplaceTargetFramework(FString& OutResult);

	static void ReplaceProjectReference(FString& OutResult);

	static void ReplaceYield(FString& OutResult);

	static void ReplaceDefinition(FString& OutResult);

	static void ReplaceProject(FString& OutResult);
};
