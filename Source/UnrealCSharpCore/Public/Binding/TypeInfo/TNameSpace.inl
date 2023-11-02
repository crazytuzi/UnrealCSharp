#pragma once

#include "FNameSpace.h"
#include "TGeneric.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Containers/ArrayBuilder.h"
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
struct TNameSpace
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<T>::Type>
struct TGenericNameSpace
{
	static TArray<FString> Get()
	{
		return TArrayBuilder<FString>()
		       .Append(TNameSpace<Type, Type>::Get())
		       .Add(TGeneric<T, T>::GetNameSpace())
		       .Build();
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, uint8>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, uint16>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, uint32>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, uint64>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, int8>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, int16>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, int32>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, int64>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, bool>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, float>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<T>> &&
                                      !std::is_same_v<std::remove_pointer_t<T>, UClass>, T>>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(std::remove_pointer_t<T>::StaticClass())};
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::ElementType::StaticClass())};
	}
};
#endif

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, FName>, T>> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsIInterface<T>::Value, T>>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::UClassType::StaticClass())};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTScriptInterface<T>::Value, T>> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsUStruct<T>::Value, T>>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::StaticStruct())};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, FString>, T>> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, FText>, T>> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTWeakObjectPtr<T>::Value, T>> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTLazyObjectPtr<T>::Value, T>> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSoftObjectPtr<T>::Value, T>> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<T, double>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTMap<T>::Value, T>>
{
	static TArray<FString> Get()
	{
		return TArrayBuilder<FString>()
		       .Append(TNameSpace<
				       typename TTemplateTypeTraits<T>::template Type<0>,
				       typename TTemplateTypeTraits<T>::template Type<0>>
			       ::Get())
		       .Append(TNameSpace<
				       typename TTemplateTypeTraits<T>::template Type<1>,
				       typename TTemplateTypeTraits<T>::template Type<1>>
			       ::Get())
		       .Add(TGeneric<T, T>::GetNameSpace())
		       .Build();
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSet<T>::Value, T>> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSubclassOf<T>::Value, T>> :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::remove_pointer_t<T>, UClass>, T>> final :
	TNameSpace<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTArray<T>::Value, T>> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsEnum<T>::Value && !TIsNotUEnum<T>::Value, T>>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(StaticEnum<T>())};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTEnumAsByte<T>::Value, T>> :
	TNameSpace<typename T::EnumType, typename T::EnumType>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSoftClassPtr<T>::Value, T>> final :
	TGenericNameSpace<T>
{
};
