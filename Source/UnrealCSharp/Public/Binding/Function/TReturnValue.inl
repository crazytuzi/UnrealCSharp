#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TReturnValue
{
};

template <typename T>
struct TPrimitiveReturnValue
{
	using Type = typename TDecay<T>::Type;

	explicit TPrimitiveReturnValue(Type&& InValue):
		Object{TPropertyValue<Type, Type>::Get(&InValue)}
	{
	}

	MonoObject* Get() const
	{
		return Object;
	}

private:
	MonoObject* Object;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint8>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint16>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint32>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint64>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int8>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int16>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int32>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int64>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, bool>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, float>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, double>::Value>::Type> :
	TPrimitiveReturnValue<T>
{
	using TPrimitiveReturnValue<T>::TPrimitiveReturnValue;
};
