#pragma once

#include "CoreMinimal.h"

#if WITH_MONO
typedef int64 IManagedHandle;

static constexpr IManagedHandle InvalidManagedHandle{};

FORCEINLINE bool IManagedHandleIsValid(const IManagedHandle InManagedHandle)
{
	return InManagedHandle != InvalidManagedHandle;
}

FORCEINLINE IManagedHandle IManagedHandleFromObject(const void* InObject)
{
	return static_cast<IManagedHandle>(reinterpret_cast<UPTRINT>(InObject));
}

FORCEINLINE IManagedHandle IManagedHandleFromObject(const IManagedHandle InManagedHandle)
{
	return InManagedHandle;
}

FORCEINLINE void* IManagedHandleToObject(const IManagedHandle InManagedHandle)
{
	return reinterpret_cast<void*>(static_cast<UPTRINT>(InManagedHandle));
}

#define MANAGED_HANDLE_FROM_OBJECT(InObject) IManagedHandleFromObject(InObject)

#define MANAGED_HANDLE_CAST_TO_OBJECT(Type, InManagedHandle) reinterpret_cast<Type>(IManagedHandleToObject(InManagedHandle))

#define MANAGED_HANDLE_TO_OBJECT(InManagedHandle) MANAGED_HANDLE_CAST_TO_OBJECT(void*, InManagedHandle)
#else
template <typename>
struct TManaged
{
	explicit operator int64() const
	{
		return Value;
	}

	bool operator==(const TManaged& InOther) const
	{
		return Value == InOther.Value;
	}

	bool operator!=(const TManaged& InOther) const
	{
		return Value != InOther.Value;
	}

	friend uint32 GetTypeHash(const TManaged& InManaged)
	{
		return ::GetTypeHash(InManaged.Value);
	}

	int64 Value{};
};

struct IManagedNull
{
	operator int64() const
	{
		return {};
	}

	template <typename T>
	operator TManaged<T>() const
	{
		return {};
	}

	template <typename T>
	friend bool operator==(const TManaged<T>& InManaged, IManagedNull)
	{
		return InManaged.Value == 0;
	}

	template <typename T>
	friend bool operator==(IManagedNull, const TManaged<T>& InManaged)
	{
		return InManaged.Value == 0;
	}

	template <typename T>
	friend bool operator!=(const TManaged<T>& InManaged, IManagedNull)
	{
		return InManaged.Value != 0;
	}

	template <typename T>
	friend bool operator!=(IManagedNull, const TManaged<T>& InManaged)
	{
		return InManaged.Value != 0;
	}
};

using IManagedHandle = TManaged<struct IManagedHandleTag>;

static constexpr IManagedHandle InvalidManagedHandle{};

FORCEINLINE bool IManagedHandleIsValid(const IManagedHandle InManagedHandle)
{
	return InManagedHandle != InvalidManagedHandle;
}

FORCEINLINE IManagedHandle IManagedHandleFromObject(const void* InObject)
{
	return IManagedHandle{static_cast<int64>(reinterpret_cast<UPTRINT>(InObject))};
}

template <typename T>
FORCEINLINE IManagedHandle IManagedHandleFromObject(TManaged<T> InManaged)
{
	return IManagedHandle{InManaged.Value};
}

#define MANAGED_HANDLE_FROM_OBJECT(InObject) IManagedHandleFromObject(InObject)

#define MANAGED_HANDLE_CAST_TO_OBJECT(Type, InManagedHandle) reinterpret_cast<Type*>(static_cast<UPTRINT>((InManagedHandle).Value))

#define MANAGED_HANDLE_TO_OBJECT(InManagedHandle) MANAGED_HANDLE_CAST_TO_OBJECT(void, InManagedHandle)
#endif
