#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TReturnValue
{
};

template <typename T>
struct TBaseReturnValue
{
	using Type = std::decay_t<T>;

	explicit TBaseReturnValue(MonoObject* InObject):
		Object(InObject)
	{
	}

	explicit TBaseReturnValue(Type&& InValue):
		Object{TPropertyValue<Type, Type>::Get(&InValue)}
	{
	}

	MonoObject* Get() const
	{
		return Object;
	}

protected:
	MonoObject* Object;
};

template <typename T>
struct TSingleReturnValue :
	TBaseReturnValue<T>
{
	using TBaseReturnValue<T>::TBaseReturnValue;
};

template <typename T>
struct TReferenceReturnValue :
	TBaseReturnValue<T>
{
	using Super = TBaseReturnValue<T>;

	using Type = typename Super::Type;

	explicit TReferenceReturnValue(Type&& InValue):
		Super(TPropertyValue<Type, Type>::Get(new Type(InValue)))
	{
	}
};

template <typename T>
struct TContainerReturnValue :
	TReferenceReturnValue<T>
{
	using TReferenceReturnValue<T>::TReferenceReturnValue;
};

template <typename T>
struct TMultiReturnValue :
	TReferenceReturnValue<T>
{
	using TReferenceReturnValue<T>::TReferenceReturnValue;
};

template <typename T>
struct TBindingReturnValue :
	TReferenceReturnValue<T>
{
	using TReferenceReturnValue<T>::TReferenceReturnValue;
};

template <typename T>
struct TScriptStructReturnValue :
	TReferenceReturnValue<T>
{
	using TReferenceReturnValue<T>::TReferenceReturnValue;
};

template <typename T>
struct TBindingEnumReturnValue :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T,
                    std::enable_if_t<
	                    std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>> &&
	                    !std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

#if UE_OBJECT_PTR
template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};
#endif

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value>> :
	TReferenceReturnValue<T>
{
	using TReferenceReturnValue<T>::TReferenceReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value>> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value>> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value>> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value>> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};
