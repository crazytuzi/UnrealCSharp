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
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Template/TIsTOptional.inl"
#endif

template <typename T, typename Enable = void>
struct TPropertyClass
{
};

template <typename T, typename Type = typename TTemplateTypeTraits<std::decay_t<T>>::Type>
struct TMultiPropertyClass
{
	static auto Get()
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
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TScriptStructPropertyClass
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TBindingEnumPropertyClass
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Byte_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_UInt16_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_UInt32_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_UInt64_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_SByte_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Int16_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Int32_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Int64_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Boolean_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Single_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsIInterface<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T, typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>>
{
	static auto Get()
	{
		return FMonoDomain::Get_Double_Class();
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundKeyMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			::Get();

		const auto FoundKeyMonoType = FMonoDomain::Class_Get_Type(FoundKeyMonoClass);

		const auto FoundKeyReflectionType = FMonoDomain::Type_Get_Object(FoundKeyMonoType);

		const auto FoundValueMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
			::Get();

		const auto FoundValueMonoType = FMonoDomain::Class_Get_Type(FoundValueMonoClass);

		const auto FoundValueReflectionType = FMonoDomain::Type_Get_Object(FoundValueMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 2);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundKeyReflectionType);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 1, FoundValueReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, ReflectionTypeMonoArray);
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			::Get();

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			::Get();

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TPropertyClass<typename std::decay_t<T>::EnumType, typename std::decay_t<T>::EnumType>
{
};

template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyClass<T>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TPropertyClass<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>>
{
	static auto Get()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			TGeneric<T, T>::GetNameSpace(), TGeneric<T, T>::GetGenericName());

		const auto FoundMonoClass = TPropertyClass<
				typename TTemplateTypeTraits<std::decay_t<T>>::Type,
				typename TTemplateTypeTraits<std::decay_t<T>>::Type>
			::Get();

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};
#endif
