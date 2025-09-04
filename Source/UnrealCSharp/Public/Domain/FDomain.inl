#pragma once

template <typename T>
auto FDomain::Array_Addr(MonoArray* InArray, const uint64 InIndex) -> T
{
	return FMonoDomain::Array_Addr<T>(InArray, InIndex);
}

template <typename T>
auto FDomain::Array_Get(MonoArray* InArray, const uint64 InIndex) -> T
{
	return FMonoDomain::Array_Get<T>(InArray, InIndex);
}

template <typename T>
auto FDomain::Array_Set(MonoArray* InArray, const uint64 InIndex, T InValue) -> void
{
	FMonoDomain::Array_Set<T>(InArray, InIndex, InValue);
}
