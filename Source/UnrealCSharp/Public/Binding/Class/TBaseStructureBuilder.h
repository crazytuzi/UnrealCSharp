#pragma once

#include "FBindingClassBuilder.h"

template <typename T>
class TBaseStructureBuilder final : public FBindingClassBuilder
{
public:
	TBaseStructureBuilder();
};

#include "TBaseStructureBuilder.inl"
