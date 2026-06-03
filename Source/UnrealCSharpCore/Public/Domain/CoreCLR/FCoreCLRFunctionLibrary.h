#pragma once

#include "CoreMinimal.h"

#if WITH_CORECLR
class UNREALCSHARPCORE_API FCoreCLRFunctionLibrary
{
public:
	static FString GetCoreCLRDirectory();

	static FString GetHostFxrPath();

	static FString GetRuntimeConfigPath();

	static FString GetHostPath();
};
#endif
