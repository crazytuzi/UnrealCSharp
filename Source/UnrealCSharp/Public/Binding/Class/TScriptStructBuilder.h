#pragma once

#include "FBindingClassBuilder.h"

template <typename T>
class TScriptStructBuilder final : public FBindingClassBuilder
{
public:
	explicit TScriptStructBuilder(const FString& InNameSpace);
};

#include "TScriptStructBuilder.inl"
