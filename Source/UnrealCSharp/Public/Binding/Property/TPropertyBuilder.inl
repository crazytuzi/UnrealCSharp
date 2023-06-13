#pragma once

#include "TPropertyGetClass.inl"
#include "Binding/TypeInfo/FTypeInfo.h"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Environment/FCSharpEnvironment.h"

template <typename T, T, typename Enable = void>
struct TPropertyBuilder
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPrimitivePropertyBuilder
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

	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result, Result>::Get();
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
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsDerivedFrom<Result, UObject*>::Value>::Type>
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

	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result, Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FName>::Value>::Type>
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

	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result, Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FString>::Value>::Type>
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

	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result, Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FText>::Value>::Type>
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

	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result, Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, double>::Value>::Type> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};
