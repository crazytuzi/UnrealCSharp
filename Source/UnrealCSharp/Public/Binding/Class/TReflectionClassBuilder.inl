#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/ScriptStruct/TScriptStructClassName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <typename T>
class TReflectionClassBuilder final : public FClassBuilder
{
public:
	explicit TReflectionClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace, TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
	}
};
