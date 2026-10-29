#pragma once

#include "CoreMinimal.h"
#include "HAL/PlatformMisc.h"

class FEnvironmentVariableScope
{
public:
	explicit FEnvironmentVariableScope(const TCHAR* InName, const TCHAR* InValue) :
		Name(InName),
		PreviousValue(FPlatformMisc::GetEnvironmentVariable(InName))
	{
		FPlatformMisc::SetEnvironmentVar(InName, InValue);
	}

	~FEnvironmentVariableScope()
	{
		FPlatformMisc::SetEnvironmentVar(*Name, *PreviousValue);
	}

	FEnvironmentVariableScope(const FEnvironmentVariableScope&) = delete;

	FEnvironmentVariableScope& operator=(const FEnvironmentVariableScope&) = delete;

private:
	FString Name;

	FString PreviousValue;
};
