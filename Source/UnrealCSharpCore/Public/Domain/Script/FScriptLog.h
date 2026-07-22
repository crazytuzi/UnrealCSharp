#pragma once

#include "CoreMinimal.h"

class UNREALCSHARPCORE_API FScriptLog
{
public:
	static void Log(const uint8* InMessage, int32 InLength, uint8 InIsError);

private:
	FScriptLog() = delete;
};
