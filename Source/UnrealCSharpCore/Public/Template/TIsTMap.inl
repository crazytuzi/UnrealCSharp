#pragma once

#include "UEVersion.h"

#if UE_T_IS_T_MAP
/**
 * Traits class which determines whether or not a type is a TMap.
 */
template <typename T>
struct TIsTMap
{
	enum { Value = false };
};

template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
struct TIsTMap<TMap<KeyType, ValueType, SetAllocator, KeyFuncs>>
{
	enum { Value = true };
};

template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
struct TIsTMap<const TMap<KeyType, ValueType, SetAllocator, KeyFuncs>>
{
	enum { Value = true };
};

template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
struct TIsTMap<volatile TMap<KeyType, ValueType, SetAllocator, KeyFuncs>>
{
	enum { Value = true };
};

template <typename KeyType, typename ValueType, typename SetAllocator, typename KeyFuncs>
struct TIsTMap<const volatile TMap<KeyType, ValueType, SetAllocator, KeyFuncs>>
{
	enum { Value = true };
};
#endif
