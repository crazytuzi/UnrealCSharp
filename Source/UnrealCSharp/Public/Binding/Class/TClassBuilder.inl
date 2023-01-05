#pragma once

template <typename T>
TClassBuilder<T>::TClassBuilder(const FString& InNameSpace):
	FBindingClassBuilder(T::StaticClass()->GetName(), InNameSpace)
{
}
