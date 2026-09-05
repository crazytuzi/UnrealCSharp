#pragma once

#if WITH_LEANCLR
class FLeanCLRLog
{
public:
	static void ErrorWriter(const char* InMessage);

private:
	FLeanCLRLog() = delete;
};
#endif
