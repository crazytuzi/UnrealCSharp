#pragma once

template <typename T>
TBaseStructureBuilder<T>::TBaseStructureBuilder(const FString& InNameSpace):
	FBindingClassBuilder(TBaseStructure<T>::Get()->GetName(), InNameSpace)
{
}
