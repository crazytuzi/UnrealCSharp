#pragma once

#include "Template/TIsUObject.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsScriptStruct.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T, auto IsProjectClass>
struct TIsProjectClass
{
	static auto Get()
	{
		if constexpr (TIsUObject<T>::Value)
		{
			return FUnrealCSharpFunctionLibrary::IsGameField(T::StaticClass());
		}
		else if constexpr (TIsUStruct<T>::Value)
		{
			return FUnrealCSharpFunctionLibrary::IsGameField(T::StaticStruct());
		}
		else if constexpr (TIsScriptStruct<T>::Value)
		{
			return FUnrealCSharpFunctionLibrary::IsGameField(TBaseStructure<T>::Get());
		}
		else
		{
			return IsProjectClass;
		}
	}
};
