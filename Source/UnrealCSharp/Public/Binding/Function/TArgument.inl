#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TArgument
{
};

template <typename T>
struct TBaseArgument
{
	using Type = std::decay_t<T>;

	TBaseArgument() = default;

	explicit TBaseArgument(MonoObject* InMonoObject):
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
		return !std::is_const_v<T> && std::is_reference_v<T>;
	}

protected:
	Type Value;
};

template <typename T>
struct TSingleArgument :
	TBaseArgument<T>
{
	using TBaseArgument<T>::TBaseArgument;
};

template <typename T>
struct TReferenceArgument :
	TBaseArgument<T>
{
	using Super = TBaseArgument<T>;

	using Super::TBaseArgument;

	using Type = typename Super::Type;

	MonoObject* Set()
	{
		return TPropertyValue<Type, Type>::Get(new Type(Super::Value));
	}
};

template <typename T>
struct TContainerArgument :
	TReferenceArgument<T>
{
	using TReferenceArgument<T>::TReferenceArgument;
};

template <typename T>
struct TMultiArgument :
	TReferenceArgument<T>
{
	using TReferenceArgument<T>::TReferenceArgument;
};

template <typename T>
struct TBindingArgument :
	TReferenceArgument<T>
{
	using TReferenceArgument<T>::TReferenceArgument;
};

template <typename T>
struct TScriptStructArgument :
	TReferenceArgument<T>
{
	using TReferenceArgument<T>::TReferenceArgument;
};

template <typename T>
struct TBindingEnumArgument :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T,
                 std::enable_if_t<
	                 std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>> &&
	                 !std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

#if UE_OBJECT_PTR
template <typename T>
struct TArgument<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};
#endif

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value>> :
	TReferenceArgument<T>
{
	using TReferenceArgument<T>::TReferenceArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value>> :
	TContainerArgument<T>
{
	using TContainerArgument<T>::TContainerArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value>> :
	TContainerArgument<T>
{
	using TContainerArgument<T>::TContainerArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value>> :
	TContainerArgument<T>
{
	using TContainerArgument<T>::TContainerArgument;
};

template <typename T>
struct TArgument<T,
                 std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};
