#pragma once

#include "CoreMinimal.h"
#include "UObject/StrongObjectPtr.h"

class UUserDefinedEnum;

class FAssetGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

	static SCRIPTCODEGENERATOR_API void Generator(const FAssetData& InAssetData,
	                                              bool bDelayedGeneratorUserDefinedEnum = false);

private:
	static void GeneratorAsset(const FAssetData& InAssetData);

private:
	static TArray<TStrongObjectPtr<UUserDefinedEnum>> UserDefinedEnums;
};
