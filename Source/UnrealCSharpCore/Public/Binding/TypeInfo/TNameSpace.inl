#pragma once

#include "FNameSpace.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

template<typename T, typename Enable = void>
struct TNameSpace
{
};

template<typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
{
	static FNameSpace* Get()
	{
		return &FPrimitiveNameSpace::Instance;
	}
};

template<typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
{
	static FNameSpace* Get()
	{
		return &FPrimitiveNameSpace::Instance;
	}
};

template<typename T>
struct TNameSpace<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value, T>::Type>
{
private:
	struct FInner final :FNameSpace
	{
		virtual FString Get() const override
		{
			return FUnrealCSharpFunctionLibrary::GetClassNameSpace(TRemovePointer<T>::Type::StaticClass());
		}
	};
	
public:
	static FNameSpace* Get()
	{
		static FInner Instance;
	
		return &Instance;
	}
};
