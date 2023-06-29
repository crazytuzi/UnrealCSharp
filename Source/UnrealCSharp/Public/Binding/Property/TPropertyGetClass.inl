#pragma once

#include "CoreMacro/ClassMacro.h"
#include "Domain/FMonoDomain.h"
#include "Variable/Constexpr.h"
#include "Bridge/FTypeBridge.h"
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

template <typename T, const char* ClassName>
struct TMultiPropertyGetClass
{
	static MonoClass* GetClass()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), ClassName);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(
				TTemplateTypeTraits<T>::Type::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(
				TTemplateTypeTraits<T>::Type::StaticClass()));

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Byte_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_UInt16_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_UInt32_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_UInt64_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_SByte_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Int16_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Int32_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Int64_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Boolean_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Single_Class();
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_NAME);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SCRIPT_INTERFACE);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(
				TTemplateTypeTraits<T>::Type::UClassType::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullInterface(
				TTemplateTypeTraits<T>::Type::UClassType::StaticClass()));

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(T::StaticStruct()),
			FUnrealCSharpFunctionLibrary::GetFullClass(T::StaticStruct()));
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_WEAK_OBJECT_PTR);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(
				TTemplateTypeTraits<T>::Type < 0 > ::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(
				TTemplateTypeTraits<T>::Type < 0 > ::StaticClass()));

		return FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T, CLASS_T_LAZY_OBJECT_PTR>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T, CLASS_T_SOFT_OBJECT_PTR>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T, CLASS_T_SUB_CLASS_OF>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
	TPropertyGetClass<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> :
	TMultiPropertyGetClass<T, CLASS_T_SOFT_CLASS_PTR>
{
};

template <typename T>
struct TPropertyGetClass<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type>
{
	static MonoClass* GetClass()
	{
		return FMonoDomain::Get_Double_Class();
	}
};
