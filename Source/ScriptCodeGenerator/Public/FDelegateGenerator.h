#pragma once

#include "CoreMinimal.h"

class FDelegateGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator(FProperty* InProperty);

private:
	friend class FGeneratorCore;

	static void Generator(FDelegateProperty* InDelegateProperty);

	static void Generator(FMulticastDelegateProperty* InMulticastDelegateProperty);

	static TSet<TPair<FString, FString>> Delegate;
};
