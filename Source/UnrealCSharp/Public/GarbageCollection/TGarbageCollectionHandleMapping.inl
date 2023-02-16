#pragma once

template <typename T>
void TGarbageCollectionHandleMapping<T>::Empty()
{
	GarbageCollectionHandle2T.Empty();
}

template <typename T>
T& TGarbageCollectionHandleMapping<T>::Emplace(TGarbageCollectionHandle<>&& InKey, T&& InValue)
{
	return GarbageCollectionHandle2T.Emplace(Forward<TGarbageCollectionHandle<>>(InKey), Forward<T>(InValue));
}

template <typename T>
int32 TGarbageCollectionHandleMapping<T>::Remove(const TGarbageCollectionHandle<>& InKey)
{
	return GarbageCollectionHandle2T.Remove(InKey);
}

template <typename T>
int32 TGarbageCollectionHandleMapping<T>::Remove(const MonoObject* InKey)
{
	for (const auto& Pair : GarbageCollectionHandle2T)
	{
		if (Pair.Key == InKey)
		{
			return GarbageCollectionHandle2T.Remove(Pair.Key);
		}
	}

	return 0;
}

template <typename T>
T* TGarbageCollectionHandleMapping<T>::Find(const MonoObject* InMonoObject)
{
	for (auto& Pair : GarbageCollectionHandle2T)
	{
		if (Pair.Key == InMonoObject)
		{
			return &Pair.Value;
		}
	}

	return nullptr;
}

template <typename T>
TMap<TGarbageCollectionHandle<>, T>& TGarbageCollectionHandleMapping<T>::Get()
{
	return GarbageCollectionHandle2T;
}
