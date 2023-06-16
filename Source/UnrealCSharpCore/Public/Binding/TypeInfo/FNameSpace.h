#pragma once

#include "CoreMacro/NamespaceMacro.h"

struct FNameSpace
{
	virtual ~FNameSpace() = default;

	virtual TArray<FString, TInlineAllocator<2>> Get() const = 0;
};

struct FPrimitiveNameSpace final : FNameSpace
{
	virtual TArray<FString, TInlineAllocator<2>> Get() const override
	{
		return {TEXT("System")};
	}

	static UNREALCSHARPCORE_API FPrimitiveNameSpace Instance;
};

struct FCommonNameSpace final : FNameSpace
{
	virtual TArray<FString, TInlineAllocator<2>> Get() const override
	{
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON)};
	}

	static UNREALCSHARPCORE_API FCommonNameSpace Instance;
};
