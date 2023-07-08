#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TInValue
{
};

template <typename T>
struct TPrimitiveInValue
{
	using Type = typename TDecay<T>::Type;

	explicit TPrimitiveInValue(MonoObject* InMonoObject):
		Value{TPropertyValue<Type, Type>::Set(InMonoObject)}
	{
	}

	Type& Get()
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
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint8>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint16>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint32>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint64>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int8>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int16>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int32>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int64>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, bool>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, float>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, double>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};
