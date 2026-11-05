#pragma once

#include "Template/TIsStaticEnum.inl"
#include "UEVersion.h"
#if UE_REGULAR_UENUM_STATIC_ENUM
#include "Misc/GeneratedTypeName.h"
#include "UObject/Class.h"
#include "UObject/UObjectGlobals.h"
#endif

template <typename T>
struct TStaticEnum
{
	static auto Get()
	{
		if constexpr (TIsStaticEnum<T>::Value)
		{
			return StaticEnum<T>();
		}
		else
		{
#if UE_REGULAR_UENUM_STATIC_ENUM
			auto Name = FString(GetGeneratedTypeName<T>());

			Name.RemoveFromStart(TEXT("enum "));

			Name.RemoveFromStart(TEXT("class "));

			return FindFirstObjectSafe<UEnum>(*Name);
#else
			return static_cast<UEnum*>(nullptr);
#endif
		}
	}
};
