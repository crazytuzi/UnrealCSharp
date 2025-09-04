#pragma once

template <typename T>
auto FMonoDomain::Array_Addr(MonoArray* InArray, const uint64 InIndex) -> T
{
	return *(T*)Array_Addr_With_Size(InArray, sizeof(T), InIndex);
}

template <typename T>
auto FMonoDomain::Array_Get(MonoArray* InArray, const uint64 InIndex) -> T
{
	return Array_Addr<T>(InArray, InIndex);
}

template <typename T>
auto FMonoDomain::Array_Set(MonoArray* InArray, const uint64 InIndex, T InValue) -> void
{
	*(T*)Array_Addr_With_Size(InArray, sizeof(T), InIndex) = InValue;
}
