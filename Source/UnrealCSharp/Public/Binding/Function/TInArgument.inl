#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TInArgument
{
};

template <typename T>
struct TPrimitiveInArgument
{
	using Type = typename TDecay<T>::Type;

	explicit TPrimitiveInArgument(MonoObject* InMonoObject):
		Value{TPropertyValue<Type, Type>::Set(InMonoObject)}
	{
	}

	Type Get() const
	{
		return Value;
	}

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(&Value);
	}

	constexpr bool IsOut() const
	{
		return TAnd<TNot<TIsConst<T>>, TIsReferenceType<T>>::Value;
	}

private:
	Type Value;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint8>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint16>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint32>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint64>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int8>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int16>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int32>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int64>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, bool>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, float>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};

template <typename T>
struct TInArgument<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, double>::Value>::Type> :
	TPrimitiveInArgument<T>
{
	using TPrimitiveInArgument<T>::TPrimitiveInArgument;
};
