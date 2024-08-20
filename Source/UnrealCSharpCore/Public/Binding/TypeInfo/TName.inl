#pragma once

#include "TGeneric.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Template/TIsTOptional.inl"
#endif

template <typename T, typename Enable = void>
struct TName
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<std::decay_t<T>>::Type>
struct TGenericName
{
	static auto Get()
	{
		return FString::Printf(TEXT(
			"%s<%s>"
		),
		                       *TGeneric<T, T>::GetTemplateName(),
		                       *TName<Type, Type>::Get()
		);
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>>
{
	static auto Get()
	{
		return FString(TEXT("byte"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>>
{
	static auto Get()
	{
		return FString(TEXT("ushort"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>>
{
	static auto Get()
	{
		return FString(TEXT("uint"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>>
{
	static auto Get()
	{
		return FString(TEXT("ulong"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>>
{
	static auto Get()
	{
		return FString(TEXT("sbyte"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>>
{
	static auto Get()
	{
		return FString(TEXT("short"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>>
{
	static auto Get()
	{
		return FString(TEXT("int"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>>
{
	static auto Get()
	{
		return FString(TEXT("long"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>>
{
	static auto Get()
	{
		return FString(TEXT("bool"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>>
{
	static auto Get()
	{
		return FString(TEXT("float"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>
{
	static auto Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(std::remove_pointer_t<std::decay_t<T>>::StaticClass());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(std::decay_t<T>::ElementType::StaticClass());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>>
{
	static auto Get()
	{
		return CLASS_F_NAME;
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsIInterface<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullInterface(std::decay_t<T>::UClassType::StaticClass());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(std::decay_t<T>::StaticStruct());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>>
{
	static auto Get()
	{
		return CLASS_F_STRING;
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>>
{
	static auto Get()
	{
		return CLASS_F_TEXT;
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	TGenericName<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>>
{
	static auto Get()
	{
		return FString(TEXT("double"));
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FString::Printf(TEXT(
			"%s<%s, %s>"
		),
		                       *TGeneric<T, T>::GetTemplateName(),
		                       *TName<
			                       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
			                       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
		                       ::Get(),
		                       *TName<
			                       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
			                       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
		                       ::Get()
		);
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>> :
	TGenericName<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>> :
	TGenericName<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(StaticEnum<std::decay_t<T>>());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TName<typename std::decay_t<T>::EnumType, typename std::decay_t<T>::EnumType>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TGenericName<T>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TName<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>> :
	TGenericName<T>
{
};
#endif
