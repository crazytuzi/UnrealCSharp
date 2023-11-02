#pragma once

#include "TGeneric.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTSubclassOf.inl"
#include "Template/TIsTSet.inl"
#include "Template/TIsTMap.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"

template <typename T, typename Enable = void>
struct TName
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<T>::Type>
struct TGenericName
{
	static FString Get()
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
struct TName<T, std::enable_if_t<std::is_same_v<T, uint8>, T>>
{
	static FString Get()
	{
		return TEXT("Byte");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, uint16>, T>>
{
	static FString Get()
	{
		return TEXT("UInt16");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, uint32>, T>>
{
	static FString Get()
	{
		return TEXT("UInt32");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, uint64>, T>>
{
	static FString Get()
	{
		return TEXT("UInt64");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, int8>, T>>
{
	static FString Get()
	{
		return TEXT("SByte");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, int16>, T>>
{
	static FString Get()
	{
		return TEXT("Int16");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, int32>, T>>
{
	static FString Get()
	{
		return TEXT("Int32");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, int64>, T>>
{
	static FString Get()
	{
		return TEXT("Int64");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, bool>, T>>
{
	static FString Get()
	{
		return TEXT("Boolean");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, float>, T>>
{
	static FString Get()
	{
		return TEXT("Single");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<T>> &&
                                 !std::is_same_v<std::remove_pointer_t<T>, UClass>, T>>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(std::remove_pointer_t<T>::StaticClass());
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TName<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(T::ElementType::StaticClass());
	}
};
#endif

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, FName>, T>>
{
	static FString Get()
	{
		return CLASS_F_NAME;
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsIInterface<T>::Value, T>>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullInterface(T::UClassType::StaticClass());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTScriptInterface<T>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsUStruct<T>::Value, T>>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(T::StaticStruct());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, FString>, T>>
{
	static FString Get()
	{
		return CLASS_F_STRING;
	}
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, FText>, T>>
{
	static FString Get()
	{
		return CLASS_F_TEXT;
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTWeakObjectPtr<T>::Value, T>> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTLazyObjectPtr<T>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSoftObjectPtr<T>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<T, double>, T>>
{
	static FString Get()
	{
		return TEXT("Double");
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTMap<T>::Value, T>>
{
	static FString Get()
	{
		return FString::Printf(TEXT(
			"%s<%s, %s>"
		),
		                       *TGeneric<T, T>::GetTemplateName(),
		                       *TName<
			                       typename TTemplateTypeTraits<T>::template Type<0>,
			                       typename TTemplateTypeTraits<T>::template Type<0>>
		                       ::Get(),
		                       *TName<
			                       typename TTemplateTypeTraits<T>::template Type<1>,
			                       typename TTemplateTypeTraits<T>::template Type<1>>
		                       ::Get()
		);
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSet<T>::Value, T>> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSubclassOf<T>::Value, T>> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, std::enable_if_t<std::is_same_v<std::remove_pointer_t<T>, UClass>, T>> :
	TName<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTArray<T>::Value, T>> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsEnum<T>::Value && !TIsNotUEnum<T>::Value, T>>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(StaticEnum<T>());
	}
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTEnumAsByte<T>::Value, T>> :
	TName<typename T::EnumType, typename T::EnumType>
{
};

template <typename T>
struct TName<T, std::enable_if_t<TIsTSoftClassPtr<T>::Value, T>> :
	TGenericName<T>
{
};
