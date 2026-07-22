#pragma once

#include "CoreMinimal.h"

struct IManagedHandle
{
	int64 Value{};

	bool operator==(const IManagedHandle& InOther) const
	{
		return Value == InOther.Value;
	}

	bool operator!=(const IManagedHandle& InOther) const
	{
		return Value != InOther.Value;
	}

	friend uint32 GetTypeHash(const IManagedHandle& InManaged)
	{
		return ::GetTypeHash(InManaged.Value);
	}
};

static constexpr IManagedHandle InvalidManagedHandle{};

FORCEINLINE bool IManagedHandleIsValid(const IManagedHandle InManagedHandle)
{
	return InManagedHandle != InvalidManagedHandle;
}

FORCEINLINE IManagedHandle IManagedHandleFromObject(const void* InObject)
{
	return IManagedHandle{static_cast<int64>(reinterpret_cast<UPTRINT>(InObject))};
}

FORCEINLINE void* IManagedHandleToObject(const IManagedHandle InManagedHandle)
{
	return reinterpret_cast<void*>(static_cast<UPTRINT>(InManagedHandle.Value));
}
