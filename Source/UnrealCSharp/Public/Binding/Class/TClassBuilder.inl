#pragma once

template <typename T>
TClassBuilder<T>::TClassBuilder():
	FBindingClassBuilder(T::StaticClass()->GetName())
{
}
