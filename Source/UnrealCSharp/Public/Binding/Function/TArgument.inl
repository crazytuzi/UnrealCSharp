#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TArgument
{
};

template <typename T, typename Enable = void>
struct TParentArgument
{
};

template <typename T>
struct TBaseArgument
{
	using Type = T;

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
		return TPropertyValue<Type, Type>::Get(const_cast<std::decay_t<T>*>(&Value));
	}

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
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
struct TStringArgument :
	TBaseArgument<std::decay_t<T>>
{
	using TBaseArgument<std::decay_t<T>>::TBaseArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};

template <typename T>
struct TParentArgument<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>> || std::is_same_v<
	                                           std::remove_pointer_t<std::remove_reference_t<T>>, UClass>, T>> :
	TBaseArgument<T>
{
	using Super = TBaseArgument<T>;

	using Super::TBaseArgument;

	using Type = typename Super::Type;

	MonoObject* Set()
	{
		if constexpr (TTypeInfo<T>::IsReference())
		{
			return Super::Set();
		}
		else
		{
			return TPropertyValue<Type, Type>::Get(new Type(Super::Value));
		}
	}
};

template <typename T>
struct TParentArgument<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>> && !std::is_same_v<
	                                           std::remove_pointer_t<std::remove_reference_t<T>>, UClass>, T>> :
	TBaseArgument<std::decay_t<T>>
{
	using Super = TBaseArgument<std::decay_t<T>>;

	using Super::TBaseArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};


template <typename T>
struct TContainerArgument :
	TParentArgument<std::decay_t<T>, std::decay_t<T>>
{
	using TParentArgument<std::decay_t<T>, std::decay_t<T>>::TParentArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};

template <typename T>
struct TMultiArgument :
	TParentArgument<T, T>
{
	using TParentArgument<T, T>::TParentArgument;
};

template <typename T>
struct TBindingArgument :
	TParentArgument<T, T>
{
	using TParentArgument<T, T>::TParentArgument;
};

template <typename T>
struct TScriptStructArgument :
	TParentArgument<T, T>
{
	using TParentArgument<T, T>::TParentArgument;
};

template <typename T>
struct TBindingEnumArgument :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T,
                 std::enable_if_t<
	                 std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>> &&
	                 !std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>, T>> :
	TBaseArgument<std::decay_t<T>>
{
	using TBaseArgument<std::decay_t<T>>::TBaseArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
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
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>> :
	TStringArgument<T>
{
	using TStringArgument<T>::TStringArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value, T>> :
	TParentArgument<T, T>
{
	using TParentArgument<T, T>::TParentArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>> :
	TStringArgument<T>
{
	using TStringArgument<T>::TStringArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>> :
	TStringArgument<T>
{
	using TStringArgument<T>::TStringArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>> :
	TContainerArgument<T>
{
	using TContainerArgument<T>::TContainerArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>> :
	TContainerArgument<T>
{
	using TContainerArgument<T>::TContainerArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>, T>> :
	TMultiArgument<std::decay_t<T>>
{
	using TMultiArgument<std::decay_t<T>>::TMultiArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>> :
	TContainerArgument<T>
{
	using TContainerArgument<T>::TContainerArgument;
};

template <typename T>
struct TArgument<T,
                 std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TSingleArgument<T>
{
	using TSingleArgument<T>::TSingleArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};
