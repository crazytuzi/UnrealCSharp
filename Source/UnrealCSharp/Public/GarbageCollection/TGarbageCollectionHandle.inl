#pragma once

#include "GarbageCollection/TGarbageCollectionHandle.h"
#include "Environment/FCSharpEnvironment.h"

template <typename T>
TGarbageCollectionHandle<T>::TGarbageCollectionHandle():
	Handle(T())
{
}

template <typename T>
TGarbageCollectionHandle<T>::TGarbageCollectionHandle(const T& InHandle):
	Handle(InHandle)
{
}

template <typename T>
TGarbageCollectionHandle<T>::operator T() const
{
	return Handle;
}

template <typename T>
TGarbageCollectionHandle<T>::operator MonoObject*() const
{
	return FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Get_Target(Handle);
}

template <typename T>
bool TGarbageCollectionHandle<T>::operator==(const TGarbageCollectionHandle& Other) const
{
	return static_cast<MonoObject*>(*this) == static_cast<MonoObject*>(Other);
}

template <typename T>
bool TGarbageCollectionHandle<T>::operator!=(const TGarbageCollectionHandle& Other) const
{
	return !(*this == Other);
}
