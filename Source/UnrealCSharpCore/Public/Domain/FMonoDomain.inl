#pragma once

template <typename T>
auto FMonoDomain::Array_Addr(MonoArray* InArray, const uint64 InIndex) -> T
{
	return *(T*)((char*)InArray->vector + sizeof(T) * InIndex);
}

template <typename T>
auto FMonoDomain::Array_Get(MonoArray* InArray, const uint64 InIndex) -> T
{
	return *(T*)((char*)InArray->vector + sizeof(T) * InIndex);
}

template <typename T>
auto FMonoDomain::Array_Set(MonoArray* InArray, const uint64 InIndex, T InValue) -> void
{
	*(T*)((char*)InArray->vector + sizeof(T) * InIndex) = InValue;
}
