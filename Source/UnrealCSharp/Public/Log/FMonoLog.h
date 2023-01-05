#pragma once

#include "mono/utils/mono-publib.h"

class FMonoLog
{
public:
	static void MonoPrintf(const char* InString, mono_bool IsStdout);

	static void MonoLog(const char* InLogDomain, const char* InLogLevel, const char* InMessage, mono_bool InFatal,
	                    void* InUserdata);

	static void Log_LogImplementation(const UTF16CHAR* InBuffer, unsigned int InReadOffset);

private:
	FMonoLog() = delete;
};
