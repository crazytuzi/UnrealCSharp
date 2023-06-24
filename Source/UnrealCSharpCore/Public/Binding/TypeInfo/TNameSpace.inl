#pragma once

#include "FNameSpace.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
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
struct TNameSpace<T, typename TEnableIf<TAnd<
	                                        TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                        TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                  ::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass())};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(
					TTemplateTypeTraits<T>::Type::UClassType::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::StaticStruct())};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(TTemplateTypeTraits<T>::Type < 0 > ::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(TTemplateTypeTraits<T>::Type::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(TTemplateTypeTraits<T>::Type::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(TTemplateTypeTraits<T>::Type::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
	TNameSpace<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type>
{
private:
	struct FInner final : FNameSpace
	{
		virtual TArray<FString, TInlineAllocator<2>> Get() const override
		{
			return {
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(TTemplateTypeTraits<T>::Type::StaticClass()),
				FCommonNameSpace::Instance.Get()[0]
			};
		}
	};

public:
	static FNameSpace* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};
