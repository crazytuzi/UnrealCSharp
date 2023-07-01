#pragma once

#include "Domain/FMonoDomain.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/MonoMacro.h"
#include "Binding/TypeInfo/TGeneric.inl"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsUStruct.inl"

template <typename T, typename Enable = void>
struct TPropertyGetClass
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<T>::Type>
struct TMultiPropertyGetClass
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyGetClass<Type, Type>::Get();

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Byte_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_UInt16_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_UInt32_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_UInt64_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_SByte_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Int16_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Int32_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Int64_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Boolean_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Single_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TAnd<
	                                               TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                               TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                         ::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsIInterface<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Double_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSet<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyGetClass<
				typename TTemplateTypeTraits<T>::template Type<0>,
				typename TTemplateTypeTraits<T>::template Type<0>>
			::Get();

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass, ReflectionTypeMonoArray);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T>
{
};


template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
	TPropertyGetClass<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyGetClass<
				typename TTemplateTypeTraits<T>::template Type<0>,
				typename TTemplateTypeTraits<T>::template Type<0>>
			::Get();

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass, ReflectionTypeMonoArray);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T>
{
};
