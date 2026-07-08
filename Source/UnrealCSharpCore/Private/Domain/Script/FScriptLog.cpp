#include "Domain/Script/FScriptLog.h"
#include "Log/UnrealCSharpLog.h"

void FScriptLog::Log(const uint8* InMessage, const int32 InLength, const uint8 InIsError)
{
#if !NO_LOGGING
	if (InMessage != nullptr)
	{
		TArray<uint8> Message;

		Message.Append(InMessage, InLength);

		Message.Add(0);

		if (InIsError != 0)
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
