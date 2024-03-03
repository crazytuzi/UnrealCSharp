#pragma once

#include "TIsUObject.inl"
#include "TIsUStruct.inl"
#include "TIsScriptStruct.inl"

template <typename T>
struct TIsReflection
{
	enum { Value = TIsUObject<T>::Value || TIsUStruct<T>::Value || TIsScriptStruct<T>::Value };
};
