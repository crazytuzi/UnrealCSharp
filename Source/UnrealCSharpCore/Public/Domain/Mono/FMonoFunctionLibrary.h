#pragma once

#include "CoreMinimal.h"

#if WITH_MONO
class UNREALCSHARPCORE_API FMonoFunctionLibrary
{
public:
	static FString GetMonoDirectory();

	static FString GetLibDirectory();

	static FString GetNetDirectory();

	static TArray<FString> GetAssemblyPath();

	static class UAssemblyLoader* GetAssemblyLoader();
};
#endif
