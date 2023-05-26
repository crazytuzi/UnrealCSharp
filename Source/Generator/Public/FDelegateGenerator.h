#pragma once

#include "CoreMinimal.h"

class FDelegateGenerator
{
public:
	static GENERATOR_API void Generator(FProperty* InProperty);

private:
	static void Generator(FDelegateProperty* InDelegateProperty);

	static void Generator(FMulticastDelegateProperty* InMulticastDelegateProperty);
};
