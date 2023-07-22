#pragma once

#include "CoreMacro/NamespaceMacro.h"

struct FPrimitiveNameSpace
{
	static TArray<FString> Get()
	{
		return {TEXT("System")};
	}
};

struct FCommonNameSpace
{
	static TArray<FString> Get()
	{
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON)};
	}
};
