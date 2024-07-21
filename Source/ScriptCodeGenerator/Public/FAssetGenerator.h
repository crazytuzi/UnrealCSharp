#pragma once

#include "CoreMinimal.h"

class FAssetGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

	static SCRIPTCODEGENERATOR_API void Generator(const FAssetData& InAssetData, bool bDelayedGeneratorUserDefinedEnum = false);

private:
	static void GeneratorAsset(const FAssetData& InAssetData);

private:
	static TArray<class UUserDefinedEnum*> UserDefinedEnums;
};
