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
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Template/TIsTOptional.inl"
#endif

template <typename T, typename Enable = void>
struct TNameSpace
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<std::decay_t<T>>::Type>
struct TGenericNameSpace
{
	static auto Get()
	{
		return TArrayBuilder<FString>()
		       .Append(TNameSpace<Type, Type>::Get())
		       .Add(TGeneric<T, T>::GetNameSpace())
		       .Build();
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>
{
	static auto Get()
	{
		return TArray<FString>{
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(std::remove_pointer_t<std::decay_t<T>>::StaticClass())
		};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return TArray<FString>{
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(std::decay_t<T>::ElementType::StaticClass())
		};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsIInterface<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return TArray<FString>{
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(std::decay_t<T>::UClassType::StaticClass())
		};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return TArray<FString>{
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(std::decay_t<T>::StaticStruct())
		};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return TArrayBuilder<FString>()
		       .Append(TNameSpace<
				       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			       ::Get())
		       .Append(TNameSpace<
				       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
				       typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
			       ::Get())
		       .Add(TGeneric<T, T>::GetNameSpace())
		       .Build();
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return TArray<FString>{
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(StaticEnum<std::decay_t<T>>())
		};
	}
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TNameSpace<typename std::decay_t<T>::EnumType, typename std::decay_t<T>::EnumType>
{
};

template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TNameSpace<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>> final :
	TGenericNameSpace<T>
{
};
#endif
