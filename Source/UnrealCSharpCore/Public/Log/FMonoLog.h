#pragma once

#include "mono/metadata/object-forward.h"

class FMonoLog
{
public:
	static void Printf(const char* InString, mono_bool IsStdout);

	static void PrintfError(const char* InString, mono_bool IsStdout);

	static void Log(const char* InLogDomain, const char* InLogLevel, const char* InMessage, mono_bool InFatal,
	                    void* InUserdata);

private:
	FMonoLog() = delete;
};
