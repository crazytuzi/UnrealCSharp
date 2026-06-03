#pragma once

#if WITH_MONO
#include "Domain/Mono/FMonoDomain.h"
#endif

template <typename T>
auto FDomain::Array_Get(const IManagedArray InArray, const uint64 InIndex) -> T
{
#if WITH_MONO
	return FMonoDomain::Array_Get<T>(InArray, InIndex);
#else
	T Result{};

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		if (const auto Value = ScriptDomain->ArrayGet(InArray, InIndex))
		{
			FMemory::Memcpy(&Result, Value, sizeof(T));
		}
	}

	return Result;
#endif
}

template <typename T>
auto FDomain::Array_Set(const IManagedArray InArray, const uint64 InIndex, T InValue) -> void
{
#if WITH_MONO
	FMonoDomain::Array_Set(InArray, InIndex, InValue);
#else
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		if (const auto Value = ScriptDomain->ArrayGet(InArray, InIndex))
		{
			FMemory::Memcpy(Value, &InValue, sizeof(T));
		}
	}
#endif
}
