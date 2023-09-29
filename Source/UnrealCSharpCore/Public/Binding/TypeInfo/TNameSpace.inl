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
#include "UEVersion.h"

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
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, uint8>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, uint16>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, uint32>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, uint64>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, int8>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, int16>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, int32>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, int64>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, bool>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, float>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TAnd<
	                                        TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                        TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                  ::Type>
#else
struct TNameSpace<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value &&
                                        !std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>
                  ::Type>
#endif
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass())};
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTObjectPtr<T>::Value, T>::Type>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::ElementType::StaticClass())};
	}
};
#endif

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, FName>, T>::Type> final :
#endif
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
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, FString>, T>::Type> final :
#endif
	FCommonNameSpace
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, FText>, T>::Type> final :
#endif
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
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<T, double>, T>::Type> final :
#endif
	FPrimitiveNameSpace
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTMap<T>::Value, T>::Type>
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
struct TNameSpace<T, typename TEnableIf<TIsTSet<T>::Value, T>::Type> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TGenericNameSpace<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TNameSpace<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> final :
#else
struct TNameSpace<T, typename TEnableIf<std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>::Type> final :
#endif
	TNameSpace<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type> final :
	TGenericNameSpace<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TAnd<TIsEnum<T>, TNot<TIsNotUEnum<T>>>::Value, T>::Type>
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(StaticEnum<T>())};
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> final :
	TGenericNameSpace<T>
{
};
