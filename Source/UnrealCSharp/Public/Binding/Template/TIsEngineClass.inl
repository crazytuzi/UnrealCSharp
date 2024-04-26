#pragma once

#include "Template/TIsUObject.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsScriptStruct.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T, bool bIsEngineClass>
struct TIsEngineClass
{
	static bool Get()
	{
		if constexpr (TIsUObject<T>::Value)
		{
			return FUnrealCSharpFunctionLibrary::IsEngineType(T::StaticClass());
		}
		else if constexpr (TIsUStruct<T>::Value)
		{
			return FUnrealCSharpFunctionLibrary::IsEngineType(T::StaticStruct());
		}
		else if constexpr (TIsScriptStruct<T>::Value)
		{
			return FUnrealCSharpFunctionLibrary::IsEngineType(TBaseStructure<T>::Get());
		}
		else
		{
			return bIsEngineClass;
		}
	}
};
