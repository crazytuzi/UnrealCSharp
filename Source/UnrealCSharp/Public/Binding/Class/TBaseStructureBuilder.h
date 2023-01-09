#pragma once

#include "FBindingClassBuilder.h"

template <typename T>
class TBaseStructureBuilder final : public FBindingClassBuilder
{
public:
	explicit TBaseStructureBuilder(const FString& InNameSpace);
};

#include "TBaseStructureBuilder.inl"
