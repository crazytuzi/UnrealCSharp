#pragma once

#include "FNameSpace.h"
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

template <typename T>
struct TInstanceNameSpace
{
	static FNameSpace* Get()
	{
		static typename T::FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TPrimitiveNameSpace
{
	static FNameSpace* Get()
	{
		return &FPrimitiveNameSpace::Instance;
	}
};

template <typename T>
struct TMultiNameSpace :
	TInstanceNameSpace<TMultiNameSpace<T>>
{
	struct FInner final : FNameSpace
	{
		virtual TArray<FString> Get() const override
		{
			return TArrayBuilder<FString>().
			       Append(TNameSpace<T, T>::Get()->Get())
			       .Add(FCommonNameSpace::Instance.Get()[0])
			       .Build();
		}
	};
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TAnd<
	                                        TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                        TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                  ::Type> final :
	TInstanceNameSpace<TNameSpace<T, T>>
{
	struct FInner final : FNameSpace
	{
		virtual TArray<FString> Get() const override
		{
			return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass())};
		}
	};
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> final :
	TMultiNameSpace<typename TTemplateTypeTraits<T>::Type::UClassType>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type> final :
	TInstanceNameSpace<TNameSpace<T, T>>
{
	struct FInner final : FNameSpace
	{
		virtual TArray<FString> Get() const override
		{
			return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::StaticStruct())};
		}
	};
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> final :
	TMultiNameSpace<typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> final :
	TMultiNameSpace<typename TTemplateTypeTraits<T>::Type>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> final :
	TMultiNameSpace<typename TTemplateTypeTraits<T>::Type>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type> final :
	TPrimitiveNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TMultiNameSpace<typename TTemplateTypeTraits<T>::Type>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> final :
	TNameSpace<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> final :
	TMultiNameSpace<typename TTemplateTypeTraits<T>::Type>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type> final :
	TInstanceNameSpace<TNameSpace<T, T>>
{
	struct FInner final : FNameSpace
	{
		virtual TArray<FString> Get() const override
		{
			return TArrayBuilder<FString>()
			       .Append(TNameSpace<
					       typename TTemplateTypeTraits<T>::template Type<0>,
					       typename TTemplateTypeTraits<T>::template Type<0>>
				       ::Get()->Get())
			       .Add(FCommonNameSpace::Instance.Get()[0])
			       .Build();
		}
	};
};
