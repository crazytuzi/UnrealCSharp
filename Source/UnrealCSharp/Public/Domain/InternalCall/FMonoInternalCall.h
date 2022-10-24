#pragma once

class FMonoInternalCall
{
public:
	static void RegisterInternalCall(const char* InName, const void* InMethod);

private:
	FMonoInternalCall() = delete;
};
