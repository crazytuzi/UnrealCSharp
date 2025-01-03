#pragma once

#include "CoreMacro/BufferMacro.h"
#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TReturnValue
{
};

template <typename T>
struct TPrimitiveReturnValue
{
	using Type = T;

	TPrimitiveReturnValue() = default;

	explicit TPrimitiveReturnValue(RETURN_BUFFER_SIGNATURE, Type&& InValue)
	{
		*(std::remove_const_t<std::decay_t<Type>>*)RETURN_BUFFER = InValue;
	}
};

template <typename T>
struct TCompoundReturnValue
{
	using Type = T;

	TCompoundReturnValue() = default;

	explicit TCompoundReturnValue(RETURN_BUFFER_SIGNATURE, Type&& InValue)
	{
		*reinterpret_cast<void**>(RETURN_BUFFER) = TPropertyValue<Type, Type>::
			template Get<TTypeInfo<Type>::IsReference()>(const_cast<std::decay_t<Type>*>(&InValue));
	}
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
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>>> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
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
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TReturnValue<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value>> :
	TCompoundReturnValue<T>
{
	using TCompoundReturnValue<T>::TCompoundReturnValue;
};
#endif
