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
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TAnd<
	                                        TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                        TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                  ::Type>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass())};
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsIInterface<T>::Value, T>::Type>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::UClassType::StaticClass())};
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::StaticStruct())};
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type> final :
	FCommonNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type> final :
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> final :
	TNameSpace<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> final :
	TGenericNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};
