#pragma once

#if WITH_CORECLR
#include "CoreMinimal.h"
#include "corehost/coreclr_delegates.h"

class FCoreCLRLog
{
public:
	static void ErrorWriter(const char_t* InMessage);

private:
	FCoreCLRLog() = delete;
};
#endif
