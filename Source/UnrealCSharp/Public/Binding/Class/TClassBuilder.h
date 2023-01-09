#pragma once

#include "FBindingClassBuilder.h"

template <typename T>
class TClassBuilder final : public FBindingClassBuilder
{
public:
	explicit TClassBuilder(const FString& InNameSpace);
};

#include "TClassBuilder.inl"
