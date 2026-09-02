#pragma once

#include "CoreMinimal.h"

#if WITH_LEANCLR
class UNREALCSHARPCORE_API FLeanCLRFunctionLibrary
{
public:
	static FString GetLeanCLRDirectory();

	static FString GetLibDirectory();
};
#endif
