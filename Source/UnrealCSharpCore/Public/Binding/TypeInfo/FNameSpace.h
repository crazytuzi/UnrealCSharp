#pragma once

#include "CoreMacro/NamespaceMacro.h"

struct FPrimitiveNameSpace
{
	static TArray<FString> Get()
	{
		return {};
	}
};

struct FCommonNameSpace
{
	static TArray<FString> Get()
	{
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)};
	}
};
