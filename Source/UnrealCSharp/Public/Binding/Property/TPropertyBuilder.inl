#pragma once

#include "TPropertyGetClass.inl"
#include "Binding/TypeInfo/FTypeInfo.h"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Variable/Constexpr.h"
#include "Template/TGetArrayLength.inl"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsUStruct.inl"

template <typename T, T, typename Enable = void>
struct TPropertyBuilder
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TTypePropertyBuilder
{
	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result, Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPrimitivePropertyBuilder :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				(FCSharpEnvironment::GetEnvironment().GetDomain()->*TPropertyGetClass<Result>::GetClass)(),
				&(FoundObject->*Member));
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = *(Result*)FCSharpEnvironment::GetEnvironment().GetDomain()->
				Object_Unbox(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member, const char* ClassName>
struct TMultiPropertyBuilder :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<Result>(
				&(FoundObject->*Member));

			if (SrcMonoObject == nullptr)
			{
				const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), ClassName);

				const auto FoundMonoClass = FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(
						TTemplateTypeTraits<Result>::Type::StaticClass()),
					FUnrealCSharpFunctionLibrary::GetFullClass(
						TTemplateTypeTraits<Result>::Type::StaticClass()));

				const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);

				SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

				FCSharpEnvironment::GetEnvironment().AddMultiReference<Result>(
					SrcMonoObject, &(FoundObject->*Member), false);
			}

			*OutValue = SrcMonoObject;
		}
	}

	static void Set(const MonoObject* InMonoObject, const MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = *(Result*)FCSharpEnvironment::GetEnvironment().GetMulti<Result>(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint8>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint16>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint32>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint64>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int8>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int16>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int32>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int64>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, bool>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, float>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TAnd<
	                        TIsDerivedFrom<typename TRemovePointer<Result>::Type, UObject>,
	                        TNot<TIsSame<typename TRemovePointer<Result>::Type, UClass>>>::Value>
                        ::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().Bind(FoundObject->*Member);
		}
	}

	static void Set(const MonoObject* InMonoObject, const MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = FCSharpEnvironment::GetEnvironment().GetObject
				<typename TRemovePointer<Result>::Type>(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FName>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			const auto FoundMonoClass = FMonoDomain::Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_NAME);

			auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
				TCHAR_TO_UTF8(*(FoundObject->*Member).ToString())));

			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass, 1, &NewMonoString);
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = Result(UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InValue, nullptr))));
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FString>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			const auto FoundMonoClass = FMonoDomain::Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

			auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
				TCHAR_TO_UTF8(*(FoundObject->*Member))));

			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass, 1, &NewMonoString);
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = Result(UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InValue, nullptr))));
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTScriptInterface<Result>::Value>::Type> :
	TMultiPropertyBuilder<Class, Result, Member, CLASS_T_SCRIPT_INTERFACE>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TScriptInterface<IInterface>>(
				&(FoundObject->*Member));

			if (SrcMonoObject == nullptr)
			{
				const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SCRIPT_INTERFACE);

				const auto FoundMonoClass = FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(
						TTemplateTypeTraits<Result>::Type::UClassType::StaticClass()),
					FUnrealCSharpFunctionLibrary::GetFullInterface(
						TTemplateTypeTraits<Result>::Type::UClassType::StaticClass()));

				const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);

				SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

				FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>>(
					SrcMonoObject, &(FoundObject->*Member), false);
			}

			*OutValue = SrcMonoObject;
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsUStruct<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(nullptr, &(FoundObject->*Member));

			if (SrcMonoObject == nullptr)
			{
				const auto FoundMonoClass = FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(Result::StaticStruct()),
					FUnrealCSharpFunctionLibrary::GetFullClass(Result::StaticStruct()));

				auto InParams = static_cast<void*>(FoundMonoClass);

				SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
					FoundMonoClass, TGetArrayLength(InParams), &InParams);

				FCSharpEnvironment::GetEnvironment().Bind(Result::StaticStruct(), false);

				FCSharpEnvironment::GetEnvironment().AddStructReference(Result::StaticStruct(), nullptr,
				                                                        &(FoundObject->*Member), SrcMonoObject, false);
			}

			*OutValue = SrcMonoObject;
		}
	}

	static void Set(const MonoObject* InMonoObject, const MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct(InValue);

			Result::StaticStruct()->CopyScriptStruct(&(FoundObject->*Member), SrcStruct);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FText>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			const auto FoundMonoClass = FMonoDomain::Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT);

			auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
				TCHAR_TO_UTF8(*(FoundObject->*Member).ToString())));

			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass, 1, &NewMonoString);
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = Result::FromString(UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InValue, nullptr))));
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTWeakObjectPtr<Result>::Value>::Type> :
	TMultiPropertyBuilder<Class, Result, Member, CLASS_T_WEAK_OBJECT_PTR>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TWeakObjectPtr<UObject>>(
				&(FoundObject->*Member));

			if (SrcMonoObject == nullptr)
			{
				const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_WEAK_OBJECT_PTR);

				const auto FoundMonoClass = FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(
						TTemplateTypeTraits<Result>::Type < 0 > ::StaticClass()),
					FUnrealCSharpFunctionLibrary::GetFullClass(
						TTemplateTypeTraits<Result>::Type < 0 > ::StaticClass()));

				const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);

				SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

				FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>>(
					SrcMonoObject, &(FoundObject->*Member), false);
			}

			*OutValue = SrcMonoObject;
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTLazyObjectPtr<Result>::Value>::Type> :
	TMultiPropertyBuilder<Class, Result, Member, CLASS_T_LAZY_OBJECT_PTR>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSoftObjectPtr<Result>::Value>::Type> :
	TMultiPropertyBuilder<Class, Result, Member, CLASS_T_SOFT_OBJECT_PTR>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, double>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsSame<typename TRemovePointer<Result>::Type, UClass>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(
				&(FoundObject->*Member));

			if (SrcMonoObject == nullptr)
			{
				const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SUB_CLASS_OF);

				const auto FoundMonoClass = FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()),
					FUnrealCSharpFunctionLibrary::GetFullClass(UObject::StaticClass()));

				const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(FoundGenericMonoClass, FoundMonoClass);

				SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(GenericClassMonoClass);

				FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(
					SrcMonoObject, &(FoundObject->*Member), false);
			}

			*OutValue = SrcMonoObject;
		}
	}

	static void Set(const MonoObject* InMonoObject, const MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InValue)->Get();
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSubclassOf<Result>::Value>::Type> :
	TMultiPropertyBuilder<Class, Result, Member, CLASS_T_SUB_CLASS_OF>
{
	static void Set(const MonoObject* InMonoObject, const MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = FCSharpEnvironment::GetEnvironment().GetMulti<Result>(InValue)->Get();
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSoftClassPtr<Result>::Value>::Type> :
	TMultiPropertyBuilder<Class, Result, Member, CLASS_T_SOFT_CLASS_PTR>
{
};
