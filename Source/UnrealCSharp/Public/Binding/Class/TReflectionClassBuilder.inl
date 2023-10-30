#pragma once

#include "TOperatorClassBuilder.inl"

template <typename T>
class TReflectionClassBuilder final : public TOperatorClassBuilder<T>
{
public:
	explicit TReflectionClassBuilder(const FString& InImplementationNameSpace):
		TOperatorClassBuilder<T>(InImplementationNameSpace)
	{
	}

	virtual bool IsReflection() const override
	{
		return true;
	}
};
