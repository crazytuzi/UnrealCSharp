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
struct TPrimitivePropertyBuilder
{
};

template <typename Class, typename Result, auto Member, typename Enable = void>
struct TCompoundPropertyBuilder
{
};

template <typename Class, typename Result, auto Member>
struct TPropertyInfoBuilder<Class, Result, Member, std::enable_if_t<!std::is_same_v<Class, void>>>
{
	static MonoObject* Get(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			return TPropertyValue<Result, Result>::Get(&(FoundObject->*Member));
		}

		return nullptr;
	}

	static void Set(const FGarbageCollectionHandle InGarbageCollectionHandle, const FGarbageCollectionHandle InValue)
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
	static MonoObject* Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		return TPropertyValue<Result, Result>::Get(const_cast<std::remove_const_t<Result>*>(Member));
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
struct TPrimitivePropertyBuilder<Class, Result, Member, std::enable_if_t<!std::is_same_v<Class, void>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static Result Get(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			return FoundObject->*Member;
		}

		return Result{};
	}

	static void Set(const FGarbageCollectionHandle InGarbageCollectionHandle, const Result InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			FoundObject->*Member = InValue;
		}
	}
};

template <typename Class, typename Result, auto Member>
struct TPrimitivePropertyBuilder<Class, Result, Member, std::enable_if_t<std::is_same_v<Class, void>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static Result Get(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		return *Member;
	}

	static void Set(const FGarbageCollectionHandle InGarbageCollectionHandle, const Result InValue)
	{
		*const_cast<std::remove_const_t<Result>*>(Member) = InValue;
	}
};

template <typename Class, typename Result, auto Member>
struct TCompoundPropertyBuilder<Class, Result, Member, std::enable_if_t<!std::is_same_v<Class, void>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static MonoObject* Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			return TPropertyValue<Result, Result>::Get(&(FoundObject->*Member), InGarbageCollectionHandle);
		}

		return nullptr;
	}
};

template <typename Class, typename Result, auto Member>
struct TCompoundPropertyBuilder<Class, Result, Member, std::enable_if_t<std::is_same_v<Class, void>>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
	static MonoObject* Get(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		return TPropertyValue<Result, Result>::Get(const_cast<std::remove_const_t<Result>*>(Member),
		                                           InGarbageCollectionHandle,
		                                           false);
	}
};

template <typename Class, typename Result, auto Member>
struct TStringPropertyBuilder :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TContainerPropertyBuilder :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TMultiPropertyBuilder :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TBindingPropertyBuilder :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TScriptStructPropertyBuilder :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, auto Member>
struct TBindingEnumPropertyBuilder :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint8>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint16>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint32>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, uint64>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int8>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int16>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int32>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, int64>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, bool>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, float>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
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

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTObjectPtr<Result>::Value>> :
	TPropertyInfoBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FName>>> :
	TStringPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTScriptInterface<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsUStruct<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FString>>> :
	TStringPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FText>>> :
	TStringPropertyBuilder<Class, Result, Member>
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
	TPrimitivePropertyBuilder<Class, Result, Member>
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
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTEnumAsByte<Result>::Value>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
	static std::underlying_type_t<typename Result::EnumType> Get(
		const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			return FoundObject->*Member;
		}

		return std::underlying_type_t<typename Result::EnumType>{};
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSoftClassPtr<Result>::Value>> :
	TMultiPropertyBuilder<Class, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, uint8>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, uint16>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, uint32>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, uint64>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, int8>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, int16>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, int32>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, int64>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, bool>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, float>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member,
                        std::enable_if_t<
	                        std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<Result>>> &&
	                        !std::is_same_v<std::remove_pointer_t<std::decay_t<Result>>, UClass>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTObjectPtr<std::decay_t<Result>>::Value>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, FName>>> :
	TStringPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTScriptInterface<std::decay_t<Result>>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsUStruct<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, FString>>> :
	TStringPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, FText>>> :
	TStringPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<Result>>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<Result>>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<Result>>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, double>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTMap<std::decay_t<Result>>::Value>> :
	TContainerPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSet<std::decay_t<Result>>::Value>> :
	TContainerPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSubclassOf<std::decay_t<Result>>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member,
                        std::enable_if_t<std::is_same_v<std::remove_pointer_t<std::decay_t<Result>>, UClass>>> :
	TPropertyInfoBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTArray<std::decay_t<Result>>::Value>> :
	TContainerPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member,
                        std::enable_if_t<TIsEnum<Result>::Value && !TIsNotUEnum<std::decay_t<Result>>::Value>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTEnumAsByte<std::decay_t<Result>>::Value>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
	static std::underlying_type_t<typename Result::EnumType> Get(
		const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		return *Member;
	}
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<Result>>::Value>> :
	TMultiPropertyBuilder<void, Result, Member>
{
};
