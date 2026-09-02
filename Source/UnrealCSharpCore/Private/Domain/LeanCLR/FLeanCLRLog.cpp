#include "Domain/LeanCLR/FLeanCLRLog.h"
#if WITH_LEANCLR
#include "Log/UnrealCSharpLog.h"

void FLeanCLRLog::ErrorWriter(const char* InMessage)
{
#if !NO_LOGGING
	UE_LOG(LogUnrealCSharp, Error, TEXT("%hs"), InMessage);
#endif
}
#endif
