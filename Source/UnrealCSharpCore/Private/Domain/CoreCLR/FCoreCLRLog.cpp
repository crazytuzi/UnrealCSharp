#include "Domain/CoreCLR/FCoreCLRLog.h"
#if WITH_CORECLR
#include "Log/UnrealCSharpLog.h"

void FCoreCLRLog::ErrorWriter(const char_t* InMessage)
{
#if !NO_LOGGING
#if PLATFORM_WINDOWS
	UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), InMessage);
#elif PLATFORM_MAC_ARM64 || PLATFORM_MAC_X86 || PLATFORM_LINUX
	UE_LOG(LogUnrealCSharp, Error, TEXT("%hs"), InMessage);
#endif
#endif
}
#endif
