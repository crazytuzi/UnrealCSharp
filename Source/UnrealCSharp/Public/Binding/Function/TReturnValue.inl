#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TReturnValue
{
};

template <typename T>
struct TBaseReturnValue
{
	using Type = T;

	TBaseReturnValue() = default;

	explicit TBaseReturnValue(MonoObject* InObject):
		Object(InObject)
	{
	}

	explicit TBaseReturnValue(Type&& InValue):
		Object{
			TPropertyValue<Type, Type>::template Get<TTypeInfo<T>::IsReference()>(
				const_cast<std::decay_t<T>*>(&InValue))
		}
	{
	}

	auto Get() const
	{
		return Object;
	}

protected:
	MonoObject* Object;
};

template <typename T>
struct TPrimitiveReturnValue :
	TBaseReturnValue<T>
{
	using TBaseReturnValue<T>::TBaseReturnValue;
};

template <typename T>
struct TCompoundReturnValue :
	TBaseReturnValue<T>
{
	using TBaseReturnValue<T>::TBaseReturnValue;
};

template <typename T>
struct TStringReturnValue :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TContainerReturnValue :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TMultiReturnValue :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TBindingReturnValue :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TScriptStructReturnValue :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TBindingEnumReturnValue :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>>> :
	TStringReturnValue<T>
{
	using TStringReturnValue<T>::TStringReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>>> :
	TStringReturnValue<T>
{
	using TStringReturnValue<T>::TStringReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>>> :
	TStringReturnValue<T>
{
	using TStringReturnValue<T>::TStringReturnValue;
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
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
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
struct TReturnValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value>> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value>> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};
#endif
