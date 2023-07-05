#pragma once

#include "Binding/Core/TPropertyValue.inl"
#include "Binding/Core/TPropertyClass.inl"
#include "Binding/TypeInfo/FTypeInfo.h"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Environment/FCSharpEnvironment.h"
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
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			*OutValue = TPropertyValue<Result, Result, false>::Get(&(FoundObject->*Member));
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = *TPropertyValue<Result, Result, false>::Set(InValue);
		}
	}

	static FTypeInfo* TypeInfo()
	{
		return TTypeInfo<Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TContainerPropertyBuilder :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Get(MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			*OutValue = TPropertyValue<Result, Result, false>::Get(&(FoundObject->*Member), InMonoObject);
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			TPropertyValue<Result, Result, false>::Set(InValue, &(FoundObject->*Member));
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint8>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint16>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint32>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint64>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int8>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int16>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int32>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int64>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, bool>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, float>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
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
	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = TPropertyValue<Result, Result, false>::Set(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FName>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTScriptInterface<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsUStruct<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			TPropertyValue<Result, Result, false>::Set(InValue, &(FoundObject->*Member));
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FString>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FText>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = TPropertyValue<Result, Result, false>::Set(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTWeakObjectPtr<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTLazyObjectPtr<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSoftObjectPtr<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, double>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTMap<Result>::Value>::Type> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSet<Result>::Value>::Type> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSubclassOf<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsSame<typename TRemovePointer<Result>::Type, UClass>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = TPropertyValue<Result, Result, false>::Set(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTArray<Result>::Value>::Type> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsEnum<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSoftClassPtr<Result>::Value>::Type> :
	TTypePropertyBuilder<Class, Result, Member>
{
};
