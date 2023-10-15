#pragma once

#include "Binding/Core/TPropertyValue.inl"
#include "UEVersion.h"

template <typename T, typename Enable = void>
struct TReturnValue
{
};

template <typename T>
struct TBaseReturnValue
{
	using Type = typename TDecay<T>::Type;

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
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint8>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, uint8>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint16>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, uint16>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint32>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, uint32>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, uint64>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, uint64>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int8>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, int8>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int16>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, int16>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int32>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, int32>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, int64>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, int64>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, bool>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, bool>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, float>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, float>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T,
                    typename TEnableIf<TAnd<
	                    TIsDerivedFrom<typename TRemovePointer<typename TDecay<T>::Type>::Type, UObject>,
	                    TNot<TIsSame<typename TRemovePointer<typename TDecay<T>::Type>::Type, UClass>>>::Value>
                    ::Type> :
#else
struct TReturnValue<T,
                    typename TEnableIf<
	                    TIsDerivedFrom<typename TRemovePointer<typename TDecay<T>::Type>::Type, UObject>::Value &&
	                    !std::is_same_v<typename TRemovePointer<typename TDecay<T>::Type>::Type, UClass>>
                    ::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

#if UE_OBJECT_PTR
template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};
#endif

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, FName>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, FName>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTScriptInterface<typename TDecay<T>::Type>::Value>::Type> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsUStruct<typename TDecay<T>::Type>::Value>::Type> :
	TReferenceReturnValue<T>
{
	using TReferenceReturnValue<T>::TReferenceReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, FString>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, FString>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, FText>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, FText>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTWeakObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTLazyObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTSoftObjectPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<typename TDecay<T>::Type, double>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<typename TDecay<T>::Type, double>>::Type> :
#endif
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTMap<typename TDecay<T>::Type>::Value>::Type> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTSet<typename TDecay<T>::Type>::Value>::Type> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTSubclassOf<typename TDecay<T>::Type>::Value>::Type> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
#if UE_T_IS_SAME
struct TReturnValue<T, typename TEnableIf<TIsSame<
	                    typename TRemovePointer<typename TDecay<T>::Type>::Type, UClass>::Value>::Type> :
#else
struct TReturnValue<T, typename TEnableIf<std::is_same_v<
	                    typename TRemovePointer<typename TDecay<T>::Type>::Type, UClass>>::Type> :
#endif
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTArray<typename TDecay<T>::Type>::Value>::Type> :
	TContainerReturnValue<T>
{
	using TContainerReturnValue<T>::TContainerReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TAnd<TIsEnum<typename TDecay<T>::Type>,
                                               TNot<TIsNotUEnum<typename TDecay<T>::Type>>>
	                    ::Value>::Type> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTEnumAsByte<typename TDecay<T>::Type>::Value>::Type> :
	TSingleReturnValue<T>
{
	using TSingleReturnValue<T>::TSingleReturnValue;
};

template <typename T>
struct TReturnValue<T, typename TEnableIf<TIsTSoftClassPtr<typename TDecay<T>::Type>::Value>::Type> :
	TMultiReturnValue<T>
{
	using TMultiReturnValue<T>::TMultiReturnValue;
};
