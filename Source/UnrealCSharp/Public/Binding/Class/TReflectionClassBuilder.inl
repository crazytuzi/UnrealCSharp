#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"

template <typename T>
class TReflectionClassBuilder final : public FClassBuilder
{
public:
	explicit TReflectionClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace,
		              TClassFullName<T>::Get(), TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
	}

	virtual bool IsReflection() const override
	{
		return true;
	}
};
