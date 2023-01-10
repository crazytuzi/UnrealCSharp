#pragma once

#include "Binding/Template/TScriptStruct.inl"

template <typename T>
TScriptStructBuilder<T>::TScriptStructBuilder(const FString& InNameSpace):
	FBindingClassBuilder(TScriptStruct<T>::Get()->GetName(), InNameSpace)
{
}
