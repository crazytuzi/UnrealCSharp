#pragma once

#include "FBindingClassBuilder.h"

template <typename T>
class TClassBuilder final : public FBindingClassBuilder
{
public:
	TClassBuilder();
};

#include "TClassBuilder.inl"
