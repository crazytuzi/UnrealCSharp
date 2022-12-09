#pragma once

template <typename T>
TBaseStructureBuilder<T>::TBaseStructureBuilder():
	FBindingClassBuilder(TBaseStructure<T>::Get()->GetName())
{
}
