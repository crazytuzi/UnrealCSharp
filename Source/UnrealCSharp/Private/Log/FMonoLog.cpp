#include "Log/FMonoLog.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Log/UnrealCSharpLog.h"

struct FRegisterLog
{
	FRegisterLog()
	{
		FBindingClassBuilder(TEXT("Log"), NAMESPACE_LOG)
			.Function("Log", static_cast<void*>(FMonoLog::Log_LogImplementation))
			.Register();
	}
};

static FRegisterLog RegisterLog;

/**
* https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Source/MonoRuntime/Private/MonoRuntime.cpp#L78
*/
void FMonoLog::MonoPrintf(const char* InString, const mono_bool IsStdout)
{
#if !NO_LOGGING
	if (0 == FCStringAnsi::Strncmp("The assembly mscorlib.dll was not found or could not be loaded", InString, 62))
	{
		UE_LOG(LogUnrealCSharp, Fatal, TEXT("%s"), ANSI_TO_TCHAR(InString));
	}
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

/**
* https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Source/MonoRuntime/Private/MonoRuntime.cpp#L97
*/
void FMonoLog::MonoLog(const char* InLogDomain, const char* InLogLevel, const char* InMessage, const mono_bool InFatal,
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

/**
* https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Source/MonoRuntime/Private/MonoLogTextWriter.cpp#L14
*/
void FMonoLog::Log_LogImplementation(const UTF16CHAR* InBuffer, const unsigned int InReadOffset)
{
#if !NO_LOGGING
	if (UE_LOG_ACTIVE(LogUnrealCSharp, Log))
	{
		GLog->Serialize(StringCast<TCHAR>(InBuffer + 2 * sizeof(void*)).Get() + InReadOffset, ELogVerbosity::Log,
		                LogUnrealCSharp.GetCategoryName());
	}
#endif
}
