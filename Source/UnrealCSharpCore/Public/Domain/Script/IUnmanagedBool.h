#pragma once

#if WITH_MONO
using IUnmanagedBool = bool;

static constexpr IUnmanagedBool IUnmanagedTrue = true;

static constexpr IUnmanagedBool IUnmanagedFalse = false;

FORCEINLINE IUnmanagedBool BoolToIUnmanagedBool(const bool InValue)
{
	return InValue;
}
#else
using IUnmanagedBool = int32;

static constexpr IUnmanagedBool IUnmanagedTrue = 1;

static constexpr IUnmanagedBool IUnmanagedFalse = 0;

FORCEINLINE IUnmanagedBool BoolToIUnmanagedBool(const bool InValue)
{
	return InValue ? 1 : 0;
}
#endif
