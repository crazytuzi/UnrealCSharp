#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TReturnArgument
{
};

template <typename T>
struct TPrimitiveReturnArgument
{
	using Type = typename TDecay<T>::Type;

	explicit TPrimitiveReturnArgument(Type&& InValue):
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
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint8>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint16>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint32>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint64>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int8>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int16>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int32>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int64>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, bool>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, float>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};

template <typename T>
struct TReturnArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, double>::Value>::Type> :
	TPrimitiveReturnArgument<T>
{
	using TPrimitiveReturnArgument<T>::TPrimitiveReturnArgument;
};
