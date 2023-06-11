#pragma once

#include "FBindingClassBuilder.h"
#include "Binding/Template/TScriptStruct.inl"

template <typename T>
class TScriptStructBuilder final : public FBindingClassBuilder
{
public:
	explicit TScriptStructBuilder(const FString& InNameSpace):
		FBindingClassBuilder(TScriptStructName<T>::Get(), InNameSpace)
	{
	}
};
