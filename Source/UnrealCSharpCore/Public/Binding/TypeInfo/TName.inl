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
#include "UEVersion.h"

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
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, uint8>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Byte");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, uint16>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("UInt16");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, uint32>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("UInt32");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, uint64>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("UInt64");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, int8>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("SByte");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, int16>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Int16");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, int32>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Int32");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, int64>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Int64");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, bool>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Boolean");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, float>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Single");
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TAnd<
	                                   TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                   TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>
                                   ::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value &&
                                   !std::is_same_v<typename TRemovePointer<T>::Type, UClass>
                                   , T>::Type>
#endif
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(TRemovePointer<T>::Type::StaticClass());
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TName<T, typename TEnableIf<TIsTObjectPtr<T>::Value, T>::Type>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(T::ElementType::StaticClass());
	}
};
#endif

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, FName>, T>::Type>
#endif
{
	static FString Get()
	{
		return CLASS_F_NAME;
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsIInterface<T>::Value, T>::Type>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullInterface(T::UClassType::StaticClass());
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(T::StaticStruct());
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, FString>, T>::Type>
#endif
{
	static FString Get()
	{
		return CLASS_F_STRING;
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, FText>, T>::Type>
#endif
{
	static FString Get()
	{
		return CLASS_F_TEXT;
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> :
	TGenericName<T>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> :
	TGenericName<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type>
#else
struct TName<T, typename TEnableIf<std::is_same_v<T, double>, T>::Type>
#endif
{
	static FString Get()
	{
		return TEXT("Double");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTMap<T>::Value, T>::Type>
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
struct TName<T, typename TEnableIf<TIsTSet<T>::Value, T>::Type> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TGenericName<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TName<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
#else
struct TName<T, typename TEnableIf<std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>::Type> :
#endif
	TName<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TAnd<TIsEnum<T>, TNot<TIsNotUEnum<T>>>::Value, T>::Type>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(StaticEnum<T>());
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> :
	TGenericName<T>
{
};
