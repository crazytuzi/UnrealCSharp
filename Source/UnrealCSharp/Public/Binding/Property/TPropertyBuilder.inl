#pragma once

#include "CoreMacro/BufferMacro.h"
#include "Binding/Core/TPropertyValue.inl"
#include "Binding/Core/TPropertyClass.inl"
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
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Template/TIsTOptional.inl"
#endif

template <typename T, T, typename Enable = void>
struct TPropertyBuilder
{
};

template <typename Class, typename Result, auto Member>
struct TPrimitivePropertyBuilder
{
	static auto Get(const FGarbageCollectionHandle InGarbageCollectionHandle, RETURN_BUFFER_SIGNATURE)
	{
		if constexpr (std::is_same_v<Class, void>)
		{
			*(std::remove_const_t<Result>*)RETURN_BUFFER = *Member;
		}
		else
		{
			if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
				FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
			{
				*(std::remove_const_t<Result>*)RETURN_BUFFER = FoundObject->*Member;
			}
		}
	}

	static auto Set(const FGarbageCollectionHandle InGarbageCollectionHandle, IN_BUFFER_SIGNATURE)
	{
		if constexpr (std::is_same_v<Class, void>)
		{
			*Member = *(Result*)IN_BUFFER;
		}
		else
		{
			if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
				FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
			{
				FoundObject->*Member = *(Result*)IN_BUFFER;
			}
		}
	}

	static auto Info()
	{
		return TTypeInfo<Result, std::is_same_v<Class, void>>::Get();
	}
};

template <typename Class, typename Result, auto Member>
struct TCompoundPropertyBuilder
{
	static auto Get(const FGarbageCollectionHandle InGarbageCollectionHandle, RETURN_BUFFER_SIGNATURE)
	{
		if constexpr (std::is_same_v<Class, void>)
		{
			*reinterpret_cast<void**>(RETURN_BUFFER) = TPropertyValue<Result, Result>::Get(
				const_cast<std::remove_const_t<Result>*>(Member),
				InGarbageCollectionHandle);
		}
		else
		{
			if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
				FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
			{
				*reinterpret_cast<void**>(RETURN_BUFFER) = TPropertyValue<Result, Result>::Get(
					&(FoundObject->*Member),
					InGarbageCollectionHandle);
			}
		}
	}

	static auto Set(const FGarbageCollectionHandle InGarbageCollectionHandle, IN_BUFFER_SIGNATURE)
	{
		if constexpr (std::is_same_v<Class, void>)
		{
			*const_cast<std::remove_const_t<Result>*>(Member) = TPropertyValue<Result, Result>::Set(
				*(FGarbageCollectionHandle*)IN_BUFFER);
		}
		else
		{
			if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
				FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
			{
				FoundObject->*Member = TPropertyValue<Result, Result>::Set(
					*(FGarbageCollectionHandle*)IN_BUFFER);
			}
		}
	}

	static auto Info()
	{
		return TTypeInfo<Result, std::is_same_v<Class, void>>::Get();
	}
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
                        std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<Result>>>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTObjectPtr<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FName>>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTScriptInterface<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsUStruct<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FString>>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, FText>>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTWeakObjectPtr<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTLazyObjectPtr<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSoftObjectPtr<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<std::is_same_v<Result, double>>> :
	TPrimitivePropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTMap<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSet<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSubclassOf<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTArray<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
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
	static auto Get(const FGarbageCollectionHandle InGarbageCollectionHandle, RETURN_BUFFER_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			*(std::underlying_type_t<typename Result::EnumType>*)RETURN_BUFFER = FoundObject->*Member;
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTSoftClassPtr<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename Class, typename Result, Result Class::* Member>
struct TPropertyBuilder<Result Class::*, Member, std::enable_if_t<TIsTOptional<Result>::Value>> :
	TCompoundPropertyBuilder<Class, Result, Member>
{
};
#endif

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
                        std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<Result>>>>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTObjectPtr<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, FName>>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTScriptInterface<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsUStruct<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, FString>>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, FText>>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, double>>> :
	TPrimitivePropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTMap<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSet<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSubclassOf<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTArray<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
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
	static auto Get(const FGarbageCollectionHandle InGarbageCollectionHandle, RETURN_BUFFER_SIGNATURE)
	{
		*(std::underlying_type_t<typename Result::EnumType>*)RETURN_BUFFER = *Member;
	}
};

template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename Result, Result* Member>
struct TPropertyBuilder<Result*, Member, std::enable_if_t<TIsTOptional<std::decay_t<Result>>::Value>> :
	TCompoundPropertyBuilder<void, Result, Member>
{
};
#endif
