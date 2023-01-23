#pragma once

#include "Binding/Template/TScriptStruct.inl"

template <typename T>
TScriptStructBuilder<T>::TScriptStructBuilder(const FString& InNameSpace):
	FBindingClassBuilder(TScriptStructName<T>::Get(), InNameSpace)
{
}
