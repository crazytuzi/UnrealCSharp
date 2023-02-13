#pragma once

#include "CoreMinimal.h"

class UNREALCSHARPCORE_API FUnrealCSharpFunctionLibrary
{
public:
	static FString GetProxyPath();

	static FString GetGamePath();

	static FString GetModuleName(const UField* InField);

	static FString GetFileName(const UField* InField);

	static FString GetOldFileName(const UField* InField, const FString& OldName);
};
