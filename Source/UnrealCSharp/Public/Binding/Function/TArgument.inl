#pragma once

#include "Binding/Core/TPropertyValue.inl"

template <typename T, typename Enable = void>
struct TArgument
{
};

template <typename T, bool bIsPrimitive = TIsPrimitive<T>::Value>
struct TBaseArgument
{
};

template <typename T, typename Enable = void>
struct TCompoundArgument
{
};

template <typename T>
struct TBaseArgument<T, true>
{
	using Type = T;

	TBaseArgument() = default;

	explicit TBaseArgument(MonoObject* InMonoObject):
		Value
		{
			*(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InMonoObject)
		}
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
	T Value;
};

template <typename T>
struct TBaseArgument<T, false>
{
	using Type = T;

	TBaseArgument() = default;

	explicit TBaseArgument(MonoObject* InMonoObject):
		Value
		{
			TPropertyValue<Type, Type>::Set(
				*static_cast<FGarbageCollectionHandle*>(
					FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InMonoObject)))
		}
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
	T Value;
};

template <typename T>
struct TPrimitiveArgument :
	TBaseArgument<T>
{
	using TBaseArgument<T>::TBaseArgument;
};

template <typename T>
struct TCompoundArgument<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>> || std::is_same_v<
	                                             std::remove_pointer_t<std::remove_reference_t<T>>, UClass>, T>> :
	TBaseArgument<T>
{
	using TBaseArgument<T>::TBaseArgument;

	using Super = TBaseArgument<T>;

	using Type = typename Super::Type;

	MonoObject* Set()
	{
		if constexpr (TTypeInfo<T>::IsReference())
		{
			return Super::Set();
		}
		else
		{
			return TPropertyValue<Type, Type>::Get(const_cast<std::decay_t<T>*>(new Type(Super::Value)));
		}
	}
};

template <typename T>
struct TCompoundArgument<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>> && !std::is_same_v<
	                                             std::remove_pointer_t<std::remove_reference_t<T>>, UClass>, T>> :
	TBaseArgument<std::decay_t<T>>
{
	using TBaseArgument<std::decay_t<T>>::TBaseArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};

template <typename T>
struct TStringArgument :
	TCompoundArgument<std::decay_t<T>, std::decay_t<T>>
{
	using TCompoundArgument<std::decay_t<T>, std::decay_t<T>>::TCompoundArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};

template <typename T>
struct TContainerArgument :
	TCompoundArgument<std::decay_t<T>, std::decay_t<T>>
{
	using TCompoundArgument<std::decay_t<T>, std::decay_t<T>>::TCompoundArgument;

	constexpr bool IsRef() const
	{
		return TTypeInfo<T>::Get()->IsRef();
	}
};

template <typename T>
struct TMultiArgument :
	TCompoundArgument<T, T>
{
	using TCompoundArgument<T, T>::TCompoundArgument;
};

template <typename T>
struct TBindingArgument :
	TCompoundArgument<T, T>
{
	using TCompoundArgument<T, T>::TCompoundArgument;
};

template <typename T>
struct TScriptStructArgument :
	TCompoundArgument<T, T>
{
	using TCompoundArgument<T, T>::TCompoundArgument;
};

template <typename T>
struct TBindingEnumArgument :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
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

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

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
	TCompoundArgument<T, T>
{
	using TCompoundArgument<T, T>::TCompoundArgument;
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
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
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
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TPrimitiveArgument<T>
{
	using TPrimitiveArgument<T>::TPrimitiveArgument;
};

template <typename T>
struct TArgument<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TMultiArgument<T>
{
	using TMultiArgument<T>::TMultiArgument;
};
