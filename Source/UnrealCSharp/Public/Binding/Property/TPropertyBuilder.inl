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
#include "Template/TIsTEnumAsByte.inl"

template <typename T, T, typename Enable = void>
struct TPropertyBuilder
{
};

template <typename Class, typename Result, auto Member, typename Enable = void>
struct TPropertyInfoBuilder
{
};

template <typename Class, typename Result, auto Member, typename Enable = void>
struct TParentPropertyBuilder
{
};

template <typename Class, typename Result, auto Member>
struct TPropertyInfoBuilder<Class, Result, Member, std::enable_if_t<!std::is_same_v<Class, void>>>
{
	static void Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			*OutValue = TPropertyValue<Result, Result>::Get(&(FoundObject->*Member));
		}
	}

	static void Set(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			FoundObject->*Member = TPropertyValue<Result, Result>::Set(InValue);
		}
	}

	static FTypeInfo* Info()
	{
		return TTypeInfo<Result>::Get();
	}
};

template <typename Class, typename Result, auto Member>
struct TPropertyInfoBuilder<Class, Result, Member, std::enable_if_t<std::is_same_v<Class, void>>>
{
	static void Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		*OutValue = TPropertyValue<Result, Result>::Get(const_cast<std::remove_const_t<Result>*>(Member));
	}

	static void Set(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InValue)
	{
		*const_cast<std::remove_const_t<Result>*>(Member) = TPropertyValue<Result, Result>::Set(InValue);
	}

	static FTypeInfo* Info()
	{
		return TTypeInfo<Result, true>::Get();
	}
};

template <typename Class, typename Result, auto Member>
struct TParentPropertyBuilder<Class, Result, Member, std::enable_if_t<!std::is_same_v<Class, void>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static void Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			*OutValue = TPropertyValue<Result, Result>::Get(&(FoundObject->*Member), InGarbageCollectionHandle);
		}
	}
};

template <typename Class, typename Result, auto Member>
struct TParentPropertyBuilder<Class, Result, Member, std::enable_if_t<std::is_same_v<Class, void>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static void Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		*OutValue = TPropertyValue<Result, Result>::Get(const_cast<std::remove_const_t<Result>*>(Member),
														InGarbageCollectionHandle,
														false);
	}
};

template <typename Class, typename Result, auto Member>
struct TContainerPropertyBuilder :
	TParentPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TMultiPropertyBuilder :
	TParentPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TBindingPropertyBuilder :
	TParentPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TScriptStructPropertyBuilder :
	TParentPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TBindingEnumPropertyBuilder :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint8>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint16>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint32>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint64>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int8>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int16>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int32>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int64>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, bool>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, float>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        std::enable_if_t<
	                        std::is_base_of_v<UObject, std::remove_pointer_t<Result>> &&
	                        !std::is_same_v<std::remove_pointer_t<Result>, UClass>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

#if UE_OBJECT_PTR
template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTObjectPtr<Result>::Value>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};
#endif

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FName>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTScriptInterface<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsUStruct<Result>::Value>> :
	TParentPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FString>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FText>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTWeakObjectPtr<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTLazyObjectPtr<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSoftObjectPtr<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, double>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTMap<Result>::Value>> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSet<Result>::Value>> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSubclassOf<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        std::enable_if_t<std::is_same_v<std::remove_pointer_t<Result>, UClass>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTArray<Result>::Value>> :
	TContainerPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member,
                        std::enable_if_t<TIsEnum<Result>::Value && !TIsNotUEnum<Result>::Value>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTEnumAsByte<Result>::Value>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSoftClassPtr<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, uint8>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, uint16>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, uint32>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, uint64>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, int8>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, int16>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, int32>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, int64>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, bool>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, float>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member,
                        std::enable_if_t<
	                        std::is_base_of_v<UObject, std::remove_pointer_t<Result>> &&
	                        !std::is_same_v<std::remove_pointer_t<Result>, UClass>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

#if UE_OBJECT_PTR
template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTObjectPtr<Result>::Value>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};
#endif

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, FName>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTScriptInterface<Result>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsUStruct<Result>::Value>> :
	TParentPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, FString>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, FText>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTWeakObjectPtr<Result>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTLazyObjectPtr<Result>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSoftObjectPtr<Result>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<Result, double>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTMap<Result>::Value>> :
	TContainerPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSet<Result>::Value>> :
	TContainerPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSubclassOf<Result>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member,
                        std::enable_if_t<std::is_same_v<std::remove_pointer_t<Result>, UClass>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTArray<Result>::Value>> :
	TContainerPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member,
                        std::enable_if_t<TIsEnum<Result>::Value && !TIsNotUEnum<Result>::Value>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTEnumAsByte<Result>::Value>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSoftClassPtr<Result>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};
