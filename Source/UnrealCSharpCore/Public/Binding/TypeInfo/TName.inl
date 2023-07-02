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
struct TName<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Byte");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("UInt16");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("UInt32");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("UInt64");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("SByte");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Int16");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Int32");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Int64");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Boolean");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Single");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TAnd<
	                                   TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                   TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>
                                   ::Value, T>::Type>
{
	static FString Get()
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(TRemovePointer<T>::Type::StaticClass());
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
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
struct TName<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
{
	static FString Get()
	{
		return CLASS_F_STRING;
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
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
struct TName<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type>
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
struct TName<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
	TName<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type> :
	TGenericName<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TName<T, typename TEnableIf<TIsEnum<T>::Value, T>::Type>
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
