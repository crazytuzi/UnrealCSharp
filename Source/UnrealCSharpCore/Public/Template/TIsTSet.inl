#pragma once

#include "UEVersion.h"

#if UE_T_IS_T_SET
/**
 * Traits class which determines whether or not a type is a TSet.
 */
template <typename T>
struct TIsTSet
{
	enum { Value = false };
};

template <typename ElementType, typename KeyFuncs, typename Allocator>
struct TIsTSet<TSet<ElementType, KeyFuncs, Allocator>>
{
	enum { Value = true };
};

template <typename ElementType, typename KeyFuncs, typename Allocator>
struct TIsTSet<const TSet<ElementType, KeyFuncs, Allocator>>
{
	enum { Value = true };
};

template <typename ElementType, typename KeyFuncs, typename Allocator>
struct TIsTSet<volatile TSet<ElementType, KeyFuncs, Allocator>>
{
	enum { Value = true };
};

template <typename ElementType, typename KeyFuncs, typename Allocator>
struct TIsTSet<const volatile TSet<ElementType, KeyFuncs, Allocator>>
{
	enum { Value = true };
};
#endif
