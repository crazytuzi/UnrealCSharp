#pragma once

#include "Domain/FMonoDomain.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/MonoMacro.h"
#include "Binding/TypeInfo/TGeneric.inl"
#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTSubclassOf.inl"
#include "Template/TIsTSet.inl"
#include "Template/TIsTMap.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"
#include "UEVersion.h"

template <typename T, typename Enable = void>
struct TPropertyClass
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<T>::Type>
struct TMultiPropertyClass
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyClass<Type, Type>::Get();

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TBindingPropertyClass
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TScriptStructPropertyClass
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TBindingEnumPropertyClass
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, uint8>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Byte_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, uint16>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_UInt16_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, uint32>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_UInt32_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, uint64>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_UInt64_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, int8>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_SByte_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, int16>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Int16_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, int32>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Int32_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, int64>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Int64_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, bool>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Boolean_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, float>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Single_Class();
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TAnd<
	                                            TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                            TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                      ::Type>
#else
struct TPropertyClass<T, typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value &&
                                            !std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>
                      ::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTObjectPtr<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};
#endif

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, FName>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsIInterface<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, FString>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, FText>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyClass<T, typename TTemplateTypeTraits<T>::template Type<0>>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyClass<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type>
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<T, double>, T>::Type>
#endif
{
	static MonoClass* Get()
	{
		return FMonoDomain::Get_Double_Class();
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTMap<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundKeyMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<T>::template Type<0>,
				typename TTemplateTypeTraits<T>::template Type<0>>
			::Get();

		const auto FoundKeyMonoType = FMonoDomain::Class_Get_Type(FoundKeyMonoClass);

		const auto FoundKeyReflectionType = FMonoDomain::Type_Get_Object(FoundKeyMonoType);

		const auto FoundValueMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<T>::template Type<1>,
				typename TTemplateTypeTraits<T>::template Type<1>>
			::Get();

		const auto FoundValueMonoType = FMonoDomain::Class_Get_Type(FoundValueMonoClass);

		const auto FoundValueReflectionType = FMonoDomain::Type_Get_Object(FoundValueMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 2);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundKeyReflectionType);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 1, FoundValueReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, ReflectionTypeMonoArray, ReflectionTypeMonoArray);
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTSet<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyClass<
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
struct TPropertyClass<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TMultiPropertyClass<T>
{
};


template <typename T>
#if UE_T_IS_SAME
struct TPropertyClass<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
#else
struct TPropertyClass<T, typename TEnableIf<std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>::Type> :
#endif
	TPropertyClass<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTArray<T>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyClass<
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
struct TPropertyClass<T, typename TEnableIf<TAnd<TIsEnum<T>, TNot<TIsNotUEnum<T>>>::Value, T>::Type>
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTEnumAsByte<T>::Value, T>::Type> :
	TPropertyClass<typename T::EnumType, typename T::EnumType>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> :
	TMultiPropertyClass<T>
{
};
