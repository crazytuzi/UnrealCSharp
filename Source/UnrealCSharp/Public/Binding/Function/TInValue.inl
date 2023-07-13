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
struct TContainerInValue
{
	using Type = typename TDecay<T>::Type;

	explicit TContainerInValue(MonoObject* InMonoObject):
		Value{TPropertyValue<Type, Type>::Set(InMonoObject)}
	{
	}

	Type& Get()
	{
		return Value;
	}

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(new Type(Value));
	}

	constexpr bool IsOut() const
	{
		return TAnd<TNot<TIsConst<T>>, TIsReferenceType<T>>::Value;
	}

private:
	Type Value;
};

template <typename T>
struct TMultiInValue
{
	using Type = typename TDecay<T>::Type;

	explicit TMultiInValue(MonoObject* InMonoObject):
		Value{TPropertyValue<Type, Type>::Set(InMonoObject)}
	{
	}

	Type& Get()
	{
		return Value;
	}

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(new Type(Value), true);
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
struct TInValue<T, typename TEnableIf<TIsTScriptInterface<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTWeakObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTLazyObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTSoftObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, double>::Value>::Type> :
	TPrimitiveInValue<T>
{
	using TPrimitiveInValue<T>::TPrimitiveInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTMap<typename TDecay<T>::Type>::Value>::Type> :
	TContainerInValue<T>
{
	using TContainerInValue<T>::TContainerInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTSet<typename TDecay<T>::Type>::Value>::Type> :
	TContainerInValue<T>
{
	using TContainerInValue<T>::TContainerInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTSubclassOf<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTArray<typename TDecay<T>::Type>::Value>::Type> :
	TContainerInValue<T>
{
	using TContainerInValue<T>::TContainerInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTSoftClassPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};
