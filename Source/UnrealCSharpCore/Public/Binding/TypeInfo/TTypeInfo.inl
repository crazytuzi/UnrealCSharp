#pragma once

#include "FTypeInfo.h"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "Variable/Constexpr.h"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsUStruct.inl"

template <typename T, typename Enable = void>
struct TTypeInfo
{
};

template <typename T>
struct TNameSpaceInner : FTypeInfo
{
	virtual FNameSpace* GetNameSpace() const override
	{
		return TNameSpace<T, T>::Get();
	}
};

template <typename T>
struct TInstanceTypeInfo
{
	static FTypeInfo* Get()
	{
		static typename T::FInner Instance;

		return &Instance;
	}
};

template <const char* ClassName>
struct TPrimitiveTypeInfo :
	TInstanceTypeInfo<TPrimitiveTypeInfo<ClassName>>
{
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return ClassName;
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_UINT8>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_UINT16>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_UINT32>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_UINT64>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_INT8>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_INT16>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_INT32>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_INT64>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_BOOL>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_FLOAT>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TAnd<
	                                       TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                       TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                 ::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FUnrealCSharpFunctionLibrary::GetFullClass(TRemovePointer<T>::Type::StaticClass());
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : FCommonTypeInfo
	{
		virtual FString GetClass() const override
		{
			return CLASS_F_NAME;
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TScriptInterface<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullInterface(
				                       TTemplateTypeTraits<T>::Type::UClassType::StaticClass())
			);
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return *FUnrealCSharpFunctionLibrary::GetFullClass(T::StaticStruct());
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : FCommonTypeInfo
	{
		virtual FString GetClass() const override
		{
			return CLASS_F_STRING;
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : FCommonTypeInfo
	{
		virtual FString GetClass() const override
		{
			return CLASS_F_TEXT;
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TWeakObjectPtr<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type < 0 > ::StaticClass())
			);
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TLazyObjectPtr<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type::StaticClass())
			);
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TSoftObjectPtr<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type::StaticClass())
			);
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type> final :
	TPrimitiveTypeInfo<CLASS_DOUBLE>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TSubclassOf<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type::StaticClass())
			);
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> final :
	TTypeInfo<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TSoftClassPtr<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type::StaticClass())
			);
		}
	};
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type> final :
	TInstanceTypeInfo<TTypeInfo<T, T>>
{
	struct FInner final : TNameSpaceInner<T>
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TArray<%s>"
			),
			                       *TTypeInfo<
				                       typename TTemplateTypeTraits<T>::template Type<0>,
				                       typename TTemplateTypeTraits<T>::template Type<0>>
			                       ::Get()->GetClass()
			);
		}
	};
};
