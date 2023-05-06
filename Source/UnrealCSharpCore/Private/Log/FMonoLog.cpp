#include "Log/FMonoLog.h"
#include "Log/UnrealCSharpLog.h"

/**
* https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Source/MonoRuntime/Private/MonoRuntime.cpp#L78
*/
void FMonoLog::Printf(const char* InString, const mono_bool IsStdout)
{
#if !NO_LOGGING
	if (UE_LOG_ACTIVE(LogUnrealCSharp, Log))
	{
		UE_LOG(LogUnrealCSharp, Log, TEXT("%s"), ANSI_TO_TCHAR(InString));

		if (!IsStdout)
		{
			GLog->Flush();
		}
	}
#endif
}

void FMonoLog::PrintfError(const char* InString, const mono_bool IsStdout)
{
#if !NO_LOGGING
	if (UE_LOG_ACTIVE(LogUnrealCSharp, Error))
	{
		UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), ANSI_TO_TCHAR(InString));

		if (!IsStdout)
		{
			GLog->Flush();
		}
	}
#endif
}

/**
* https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Source/MonoRuntime/Private/MonoRuntime.cpp#L97
*/
void FMonoLog::Log(const char* InLogDomain, const char* InLogLevel, const char* InMessage, const mono_bool InFatal,
                       void* InUserdata)
{
#if !NO_LOGGING
	if (InFatal || 0 == FCStringAnsi::Strncmp("error", InLogLevel, 5))
	{
		UE_LOG(LogUnrealCSharp, Fatal, TEXT("%s%s%s"), InLogDomain != nullptr ? ANSI_TO_TCHAR(InLogDomain) : TEXT(""),
		       InLogDomain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(InMessage));
	}
	else if (0 == FCStringAnsi::Strncmp("warning", InLogLevel, 7))
	{
		UE_LOG(LogUnrealCSharp, Warning, TEXT("%s%s%s"), InLogDomain != nullptr ? ANSI_TO_TCHAR(InLogDomain) : TEXT(""),
		       InLogDomain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(InMessage));
	}
	else if (0 == FCStringAnsi::Strncmp("critical", InLogLevel, 8))
	{
		UE_LOG(LogUnrealCSharp, Error, TEXT("%s%s%s"), InLogDomain != nullptr ? ANSI_TO_TCHAR(InLogDomain) : TEXT(""),
		       InLogDomain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(InMessage));
	}
	else
	{
		UE_LOG(LogUnrealCSharp, Log, TEXT("%s%s%s"), InLogDomain != nullptr ? ANSI_TO_TCHAR(InLogDomain) : TEXT(""),
		       InLogDomain != nullptr ? TEXT(": ") : TEXT(""), ANSI_TO_TCHAR(InMessage));
	}
#endif
}
