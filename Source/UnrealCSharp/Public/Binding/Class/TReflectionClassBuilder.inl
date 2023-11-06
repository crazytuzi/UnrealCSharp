#pragma once

#include "TClassBuilder.inl"

template <typename T>
class TReflectionClassBuilder final : public TClassBuilder<T>
{
public:
	explicit TReflectionClassBuilder(const FString& InImplementationNameSpace):
		TClassBuilder<T>(InImplementationNameSpace)
	{
	}

	virtual bool IsReflection() const override
	{
		return true;
	}
};
