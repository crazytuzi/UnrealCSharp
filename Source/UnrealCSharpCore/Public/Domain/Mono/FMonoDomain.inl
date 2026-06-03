#pragma once

#if WITH_MONO
template <typename T>
auto FMonoDomain::Array_Addr(const IManagedArray InManagedArray, const uint64 InIndex) -> T
{
	return *(T*)((char*)InManagedArray->vector + sizeof(T) * InIndex);
}

template <typename T>
auto FMonoDomain::Array_Get(const IManagedArray InManagedArray, const uint64 InIndex) -> T
{
	return *(T*)((char*)InManagedArray->vector + sizeof(T) * InIndex);
}

template <typename T>
auto FMonoDomain::Array_Set(const IManagedArray InManagedArray, const uint64 InIndex, T InValue) -> void
{
	*(T*)((char*)InManagedArray->vector + sizeof(T) * InIndex) = InValue;
}
#endif
