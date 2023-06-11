#pragma once

#include "FTypeInfo.h"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"

template<typename T, typename Enable = void>
struct TTypeInfo
{
};

template<typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("Int32");
		}
	};
	
public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template<typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
{
private:
	class FInner final :public FPrimitiveTypeInfo
	{
	public:
		virtual FString GetClass() const override
		{
			return TEXT("Single");
		}
	};
	
public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template<typename T>
struct TTypeInfo<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value, T>::Type>
{
private:
	class FInner final :public FPrimitiveTypeInfo
	{
	public:
		virtual FString GetClass() const override
		{
			return FUnrealCSharpFunctionLibrary::GetFullClass(TRemovePointer<T>::Type::StaticClass());
		}
		
		virtual FNameSpace* GetNameSpace() const override
		{
			return TNameSpace<T,T>::Get();
		}
	};
	
public:
	static FTypeInfo* Get()
	{
		static FInner Instance;
	
		return &Instance;
	}
};
