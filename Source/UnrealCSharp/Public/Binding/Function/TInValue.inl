#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TInValue
{
};

template <typename T>
struct TBaseInValue
{
	using Type = typename TDecay<T>::Type;

	TBaseInValue() = default;

	explicit TBaseInValue(MonoObject* InMonoObject):
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

protected:
	Type Value;
};

template <typename T>
struct TSingleInValue :
	TBaseInValue<T>
{
	using TBaseInValue<T>::TBaseInValue;
};

template <typename T>
struct TContainerInValue :
	TBaseInValue<T>
{
	using Super = TBaseInValue<T>;

	using Super::TBaseInValue;

	using Type = typename Super::Type;

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(new Type(Super::Value));
	}
};

template <typename T>
struct TMultiInValue :
	TBaseInValue<T>
{
	using Super = TBaseInValue<T>;

	using Super::TBaseInValue;

	using Type = typename Super::Type;

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(new Type(Super::Value), true);
	}
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint8>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint16>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint32>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint64>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int8>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int16>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int32>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int64>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, bool>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, float>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T,
                typename TEnableIf<TAnd<
	                TIsDerivedFrom<typename TRemovePointer<typename TDecay<T>::Type>::Type, UObject>,
	                TNot<TIsSame<typename TRemovePointer<typename TDecay<T>::Type>::Type, UClass>>>::Value>
                ::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, FName>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTScriptInterface<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsUStruct<typename TDecay<T>::Type>::Value>::Type> :
	TBaseInValue<T>
{
	using Super = TBaseInValue<T>;

	using Super::TBaseInValue;

	using Type = typename Super::Type;

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(new Type(Super::Value), true);
	}
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, FString>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, FText>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
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
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
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
struct TInValue<T, typename TEnableIf<TIsSame<typename TRemovePointer<typename TDecay<T>::Type>::Type,
                                              UClass>::Value>::Type> :
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
struct TInValue<T, typename TEnableIf<TIsEnum<typename TDecay<T>::Type>::Value>::Type> :
	TSingleInValue<T>
{
	using TSingleInValue<T>::TSingleInValue;
};

template <typename T>
struct TInValue<T, typename TEnableIf<TIsTSoftClassPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiInValue<T>
{
	using TMultiInValue<T>::TMultiInValue;
};
