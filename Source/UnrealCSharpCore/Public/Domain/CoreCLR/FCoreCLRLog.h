#pragma once

#if WITH_CORECLR
#include "CoreMinimal.h"
#include "corehost/coreclr_delegates.h"

class FCoreCLRLog
{
public:
	static void ErrorWriter(const char_t* InMessage);

	static void Log(const uint8* InMessage, int32 InLength, bool InIsError);

private:
	FCoreCLRLog() = delete;
};
#endif
