#pragma once

#include "CoreMacro/NamespaceMacro.h"

struct FNameSpace
{
	virtual ~FNameSpace() = default;

	virtual FString Get() const = 0;
};

struct FPrimitiveNameSpace final : FNameSpace
{
	virtual FString Get() const override
	{
		return TEXT("System");
	}

	static FPrimitiveNameSpace Instance;
};

struct FStringNameSpace final : FNameSpace
{
	virtual FString Get() const override
	{
		return COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON);
	}

	static FStringNameSpace Instance;
};
