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

void FCoreCLRLog::Log(const uint8* InMessage, const int32 InLength, const bool InIsError)
{
#if !NO_LOGGING
	if (InMessage != nullptr)
	{
		TArray<uint8> Message;

		Message.Append(InMessage, InLength);

		Message.Add(0);

		if (InIsError)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("%s"),
			       *FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(Message.GetData()))));
		}
		else
		{
			UE_LOG(LogUnrealCSharp, Log, TEXT("%s"),
			       *FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(Message.GetData()))));
		}
	}
#endif
}
#endif
