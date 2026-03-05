#pragma once

#include "Domain/FDomain.h"
#include "Bridge/FTypeBridge.h"
#include "Binding/TypeInfo/TGeneric.inl"
#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"
#include "UEVersion.h"
#include "Reflection/FReflectionRegistry.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Template/TIsTOptional.inl"
#endif

template <typename T, typename Enable = void>
struct TPropertyClass
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>>
struct TMultiPropertyClass
{
	static auto Get()
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetClass(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundClass = TPropertyClass<Type, Type>::Get();

		return FTypeBridge::MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}
};

template <typename T>
struct TBindingPropertyClass
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TScriptStructPropertyClass
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TBindingEnumPropertyClass
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetByteClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetUInt16Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetUInt32Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetUInt64Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetSByteClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetInt16Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetInt32Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetInt64Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetBooleanClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetSingleClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<
	                      std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetNameClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsIInterface<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsUStruct<std::remove_pointer_t<std::decay_t<T>>>::Value, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetStringClass();
	}
};

#if UE_F_UTF8_STR_PROPERTY
template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FUtf8String>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetUtf8StringClass();
	}
};
#endif

#if UE_F_ANSI_STR_PROPERTY
template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FAnsiString>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetAnsiStringClass();
	}
};
#endif

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetTextClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetDoubleClass();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetClass(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundKeyClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>,
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>>
			::Get();

		const auto FoundValueClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
			::Get();

		const auto ReflectionTypeArray = FReflectionRegistry::Get().GetObjectClass()->NewArray(2);

		FDomain::Array_Set(ReflectionTypeArray, 0, FoundKeyClass->GetReflectionType());

		FDomain::Array_Set(ReflectionTypeArray, 1, FoundValueClass->GetReflectionType());

		return FTypeBridge::MakeGenericTypeInstance(FoundGenericClass, ReflectionTypeArray);
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FReflectionRegistry::Get().GetClass<T>();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TPropertyClass<typename std::decay_t<T>::EnumType, typename std::decay_t<T>::EnumType>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};
#endif
