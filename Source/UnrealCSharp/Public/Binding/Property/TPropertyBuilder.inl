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
#include "Template/TIsTSubclassOf.inl"
#include "Template/TIsTSet.inl"
#include "Template/TIsTMap.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "UEVersion.h"

template <typename T, T, typename Enable = void>
struct TPropertyBuilder
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyInfoBuilder
{
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InMonoObject))
		{
			*OutValue = TPropertyValue<Result, Result>::Get(&(FoundObject->*Member));
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InMonoObject))
		{
			FoundObject->*Member = TPropertyValue<Result, Result>::Set(InValue);
		}
	}

	static FTypeInfo* Info()
	{
		return TTypeInfo<Result>::Get();
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TContainerPropertyBuilder :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static void Get(MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InMonoObject))
		{
			*OutValue = TPropertyValue<Result, Result>::Get(&(FoundObject->*Member), InMonoObject);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint8>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, uint8>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint16>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, uint16>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint32>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, uint32>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, uint64>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, uint64>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int8>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, int8>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int16>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, int16>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int32>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, int32>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int64>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, int64>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, bool>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, bool>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, float>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, float>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TAnd<
	                        TIsDerivedFrom<typename TRemovePointer<Result>::Type, UObject>,
	                        TNot<TIsSame<typename TRemovePointer<Result>::Type, UClass>>>::Value>
                        ::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<
	                        TIsDerivedFrom<typename TRemovePointer<Result>::Type, UObject>::Value &&
	                        !std::is_same_v<typename TRemovePointer<Result>::Type, UClass>>
                        ::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FName>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, FName>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTScriptInterface<Result>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsUStruct<Result>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FString>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, FString>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, FText>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, FText>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTWeakObjectPtr<Result>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTLazyObjectPtr<Result>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSoftObjectPtr<Result>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, double>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member, typename TEnableIf<std::is_same_v<Result, double>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
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
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
#if UE_T_IS_SAME
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsSame<typename TRemovePointer<Result>::Type, UClass>::Value>::Type> :
#else
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<std::is_same_v<typename TRemovePointer<Result>::Type, UClass>>::Type> :
#endif
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTArray<Result>::Value>::Type> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TAnd<TIsEnum<Result>, TNot<TIsNotUEnum<Result>>>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        typename TEnableIf<TIsTSoftClassPtr<Result>::Value>::Type> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};
