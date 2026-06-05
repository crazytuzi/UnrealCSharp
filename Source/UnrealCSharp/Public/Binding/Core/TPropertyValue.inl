#pragma once

#include "TPropertyClass.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FSetHelper.h"
#include "Reflection/Container/FMapHelper.h"
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
#include "UObject/PropertyOptional.h"
#endif

template <typename T, typename Enable = void>
struct TPropertyValue
{
};

template <typename T>
struct TPrimitivePropertyValue
{
	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		return TPropertyClass<T, T>::Get()->Value_Box(InMember);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		return TPropertyClass<T, T>::Get()->Value_Box(InMember);
	}

	static auto Get(const IManagedObject InManagedObject)
	{
		return Get(MANAGED_HANDLE_FROM_OBJECT(InManagedObject));
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		return *static_cast<std::decay_t<T>*>(FDomain::Object_Unbox(InManagedHandle));
	}
};

template <typename T>
struct TCompoundPropertyValue
{
	static auto Get(const IManagedObject InManagedObject)
	{
		return T::Get(TPropertyClass<typename TTemplateTypeTraits<T>::template Type<>,
		                             typename TTemplateTypeTraits<T>::template Type<>>::Get()->GetGCHandle(
			InManagedObject));
	}
};

template <typename T, typename Enable = void>
struct TBindingPropertyValue
{
};

template <typename T, typename Enable = void>
struct TScriptStructPropertyValue
{
};

template <typename T>
struct TStringPropertyValue :
	TCompoundPropertyValue<TStringPropertyValue<T>>
{
	using TCompoundPropertyValue<TStringPropertyValue<T>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetStringObject<std::decay_t<T>>(InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddStringReference<std::decay_t<T>, false, true>(
				FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle), InMember);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcManagedHandle = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStringReference<std::decay_t<T>, false, false>(
				FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle), InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStringReference<std::decay_t<T>, true, false>(
				FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle), new std::decay_t<T>(*InMember));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		return std::decay_t<T>(*FCSharpEnvironment::GetEnvironment().GetString<std::decay_t<T>>(InManagedHandle));
	}
};

template <typename T>
struct TMultiPropertyValue :
	TCompoundPropertyValue<TMultiPropertyValue<T>>
{
	using TCompoundPropertyValue<TMultiPropertyValue<T>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetMultiObject<std::decay_t<T>>(InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>, false, true>(
				FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle), InMember);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcManagedHandle = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>, false, false>(
				FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle), InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>, true, false>(
				FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle), new std::decay_t<T>(*InMember));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle) -> T
	{
		return *(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetMulti<std::decay_t<T>>(InManagedHandle);
	}
};

template <typename T>
struct TBindingPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>> :
	TCompoundPropertyValue<
		TBindingPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>>
{
	using TCompoundPropertyValue<
		TBindingPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetBinding(InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

			FCSharpEnvironment::GetEnvironment().AddBindingReference(
				InManagedHandle, FoundClass, SrcManagedHandle, InMember);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, false>(
				FoundClass, SrcManagedHandle, InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, true>(
				FoundClass, SrcManagedHandle, new std::decay_t<T>(*InMember));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle) -> T
	{
		return *FCSharpEnvironment::GetEnvironment().GetBinding<std::decay_t<T>>(InManagedHandle);
	}
};

template <typename T>
struct TBindingPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>> :
	TCompoundPropertyValue<
		TBindingPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>>
{
	using TCompoundPropertyValue<
		TBindingPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetBinding(*InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

			FCSharpEnvironment::GetEnvironment().AddBindingReference(
				InManagedHandle, FoundClass, SrcManagedHandle, *InMember);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, false>(
				FoundClass, SrcManagedHandle, *InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, true>(
				FoundClass, SrcManagedHandle, new std::decay_t<T>(**InMember));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle) -> std::decay_t<T>
	{
		return FCSharpEnvironment::GetEnvironment().GetBinding<
			std::remove_pointer_t<std::remove_reference_t<T>>>(InManagedHandle);
	}
};

template <typename T>
struct TScriptStructPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>> :
	TCompoundPropertyValue<
		TScriptStructPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>>
{
	using TCompoundPropertyValue<
		TScriptStructPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetObject(
			TBaseStructure<std::decay_t<T>>::Get(), InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

			FCSharpEnvironment::GetEnvironment().Bind<false>(TBaseStructure<std::decay_t<T>>::Get());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InManagedHandle, TBaseStructure<std::decay_t<T>>::Get(), InMember, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

		FCSharpEnvironment::GetEnvironment().Bind<false>(TBaseStructure<std::decay_t<T>>::Get());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				TBaseStructure<std::decay_t<T>>::Get(), InMember, SrcManagedHandle);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				TBaseStructure<std::decay_t<T>>::Get(), new std::decay_t<T>(*InMember), SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle) -> T
	{
		return *FCSharpEnvironment::GetEnvironment().GetStruct<std::decay_t<T>>(InManagedHandle);
	}
};

template <typename T>
struct TScriptStructPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>> :
	TCompoundPropertyValue<
		TScriptStructPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>>
{
	using TCompoundPropertyValue<
		TScriptStructPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetObject(
			TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(), *InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

			FCSharpEnvironment::GetEnvironment().Bind<false>(
				TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InManagedHandle, TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(),
				*InMember, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

		FCSharpEnvironment::GetEnvironment().Bind<false>(
			TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(), InMember,
				SrcManagedHandle);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(), new std::decay_t<T>(*InMember),
				SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		return FCSharpEnvironment::GetEnvironment().GetStruct<std::decay_t<std::remove_pointer_t<T>>>(InManagedHandle);
	}
};

template <typename T>
struct TBindingEnumPropertyValue :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>> :
	TCompoundPropertyValue<
		TPropertyValue<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>>
{
	using TCompoundPropertyValue<
		TPropertyValue<T,
		               std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>>::Get ;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle& InManagedHandle)
	{
		return MANAGED_HANDLE_TO_OBJECT(MANAGED_HANDLE_FROM_OBJECT(FCSharpEnvironment::GetEnvironment().Bind(
			std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<std::decay_t<T>>>>(*InMember))));
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		return MANAGED_HANDLE_TO_OBJECT(MANAGED_HANDLE_FROM_OBJECT(FCSharpEnvironment::GetEnvironment().Bind(
			std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<std::decay_t<T>>>>(*InMember))));
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<std::remove_pointer_t<std::decay_t<T>>>(InManagedHandle);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>> :
	TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>>>
{
	using TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>>>::Get;

	static auto Get(T* InMember, const IManagedHandle& InManagedHandle)
	{
		return MANAGED_HANDLE_TO_OBJECT(FCSharpEnvironment::GetEnvironment().Bind(*InMember));
	}

	template <auto IsReference>
	static auto Get(T* InMember)
	{
		return MANAGED_HANDLE_TO_OBJECT(FCSharpEnvironment::GetEnvironment().Bind(*InMember));
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<typename T::ElementType>(InManagedHandle);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>> :
	TStringPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value &&
                                          !std::is_pointer_v<std::remove_reference_t<T>>, T>> :
	TCompoundPropertyValue<
		TPropertyValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value &&
		                                   !std::is_pointer_v<std::remove_reference_t<T>>, T>>>
{
	using TCompoundPropertyValue<
		TPropertyValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value &&
		                                   !std::is_pointer_v<std::remove_reference_t<T>>, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetObject(
			std::decay_t<T>::StaticStruct(), InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

			FCSharpEnvironment::GetEnvironment().Bind<false>(std::decay_t<T>::StaticStruct());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InManagedHandle, std::decay_t<T>::StaticStruct(), InMember, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

		FCSharpEnvironment::GetEnvironment().Bind<false>(std::decay_t<T>::StaticStruct());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				std::decay_t<T>::StaticStruct(), InMember, SrcManagedHandle);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				std::decay_t<T>::StaticStruct(), new std::decay_t<T>(*InMember), SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle) -> T
	{
		return *FCSharpEnvironment::GetEnvironment().GetStruct<std::decay_t<T>>(InManagedHandle);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsUStruct<std::remove_pointer_t<std::decay_t<T>>>::Value &&
                                          std::is_pointer_v<std::remove_reference_t<T>>, T>> :
	TCompoundPropertyValue<
		TPropertyValue<T, std::enable_if_t<TIsUStruct<std::remove_pointer_t<std::decay_t<T>>>::Value &&
		                                   std::is_pointer_v<std::remove_reference_t<T>>, T>>>
{
	using TCompoundPropertyValue<
		TPropertyValue<T, std::enable_if_t<TIsUStruct<std::remove_pointer_t<std::decay_t<T>>>::Value &&
		                                   std::is_pointer_v<std::remove_reference_t<T>>, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetObject(
			std::remove_pointer_t<std::decay_t<T>>::StaticStruct(), *InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

			FCSharpEnvironment::GetEnvironment().Bind<false>(std::remove_pointer_t<std::decay_t<T>>::StaticStruct());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InManagedHandle, std::remove_pointer_t<std::decay_t<T>>::StaticStruct(), *InMember,
				SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto SrcManagedHandle = MANAGED_HANDLE_FROM_OBJECT(FoundClass->NewObject());

		FCSharpEnvironment::GetEnvironment().Bind<false>(std::remove_pointer_t<std::decay_t<T>>::StaticStruct());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				std::remove_pointer_t<std::decay_t<T>>::StaticStruct(), *InMember, SrcManagedHandle);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				std::remove_pointer_t<std::decay_t<T>>::StaticStruct(),
				new std::remove_pointer_t<std::decay_t<T>>(**InMember), SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle) -> T
	{
		return FCSharpEnvironment::GetEnvironment().GetStruct<std::remove_pointer_t<std::decay_t<T>>>(InManagedHandle);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>> :
	TStringPropertyValue<T>
{
};

#if UE_F_UTF8_STR_PROPERTY
template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FUtf8String>, T>> :
	TStringPropertyValue<T>
{
};
#endif

#if UE_F_ANSI_STR_PROPERTY
template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FAnsiString>, T>> :
	TStringPropertyValue<T>
{
};
#endif

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>> :
	TStringPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>> :
	TPrimitivePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>> :
	TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>>
{
	using TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetContainerObject<FMapHelper>(InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto KeyProperty = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                                nullptr, "", EObjectFlags::RF_Transient);

			KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			const auto ValueProperty = FTypeBridge::Factory<>(
				FoundClass->GetGenericArgument(1), nullptr, "", EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			SrcManagedHandle = FoundClass->NewObject();

			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty,
			                                      InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				InManagedHandle, InMember, MapHelper, FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto KeyProperty = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
		                                                nullptr, "", EObjectFlags::RF_Transient);

		KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

		const auto ValueProperty = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(1),
		                                                  nullptr, "", EObjectFlags::RF_Transient);

		ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

		auto SrcManagedHandle = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty,
			                                      InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				MapHelper, FoundClass, SrcManagedHandle);
		}
		else
		{
			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty,
			                                      new std::decay_t<T>(*InMember), true, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				MapHelper, FoundClass, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		std::decay_t<T> Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InManagedHandle);

		for (auto Index = 0; Index < SrcContainer->GetMaxIndex(); ++Index)
		{
			if (SrcContainer->IsValidIndex(Index))
			{
				Value.Add(*static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>*>
				          (SrcContainer->GetEnumeratorKey(Index)),
				          *static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>*>
				          (SrcContainer->GetEnumeratorValue(Index)));
			}
		}

		return Value;
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>> :
	TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>>>
{
	using TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                             nullptr, "", EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			SrcManagedHandle = FoundClass->NewObject();

			const auto SetHelper = new FSetHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				InManagedHandle, InMember, SetHelper, FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(), nullptr,
		                                             "", EObjectFlags::RF_Transient);

		Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

		auto SrcManagedHandle = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto SetHelper = new FSetHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				SetHelper, FoundClass, SrcManagedHandle);
		}
		else
		{
			const auto SetHelper = new FSetHelper(Property, new std::decay_t<T>(*InMember), true, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				SetHelper, FoundClass, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		std::decay_t<T> Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle);

		for (auto Index = 0; Index < SrcContainer->GetMaxIndex(); ++Index)
		{
			if (SrcContainer->IsValidIndex(Index))
			{
				Value.Add(
					*static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>*>(SrcContainer->
						GetEnumerator(Index)));
			}
		}

		return Value;
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>> :
	TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>>
{
	using TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InMember);

		if (!IManagedHandleIsValid(SrcManagedHandle))
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                             nullptr, "", EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			SrcManagedHandle = FoundClass->NewObject();

			const auto ArrayHelper = new FArrayHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				InManagedHandle, InMember, ArrayHelper, FoundClass, MANAGED_HANDLE_FROM_OBJECT(SrcManagedHandle));
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(), nullptr,
		                                             "", EObjectFlags::RF_Transient);

		Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

		auto SrcManagedHandle = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto ArrayHelper = new FArrayHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, FoundClass, SrcManagedHandle);
		}
		else
		{
			const auto ArrayHelper = new FArrayHelper(Property, new std::decay_t<T>(*InMember), true, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, FoundClass, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InManagedHandle);

		return std::decay_t<T>(
			static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>*>
			(SrcContainer->GetScriptArray()->GetData()),
			SrcContainer->Num());
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>> :
	TPrimitivePropertyValue<T>
{
	using TPrimitivePropertyValue<T>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		return TPropertyClass<T, T>::Get()->Value_Box(InMember);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		return TPropertyClass<T, T>::Get()->Value_Box(InMember);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		return static_cast<std::decay_t<T>>(*static_cast<uint8*>(FDomain::Object_Unbox(InManagedHandle)));
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TPrimitivePropertyValue<T>
{
	using TPrimitivePropertyValue<T>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle InManagedHandle)
	{
		return TPropertyClass<T, T>::Get()->Value_Box(InMember);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		return TPropertyClass<T, T>::Get()->Value_Box(InMember);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>> :
	TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>>>
{
	using TCompoundPropertyValue<TPropertyValue<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>>>::Get;

	static auto Get(std::decay_t<T>* InMember, const IManagedHandle& InManagedHandle)
	{
		auto SrcManagedHandle = FCSharpEnvironment::GetEnvironment().GetOptionalObject<FOptionalHelper>(InMember);

		if (SrcManagedHandle == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                             nullptr, "", EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(Property);

			SrcManagedHandle = FoundClass->NewObject();

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, InMember,
			                                                false, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, true>(
				InMember, OptionalHelper, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

		const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(), nullptr,
		                                             "", EObjectFlags::RF_Transient);

		Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

		OptionalProperty->SetValueProperty(Property);

		auto SrcManagedHandle = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, InMember,
			                                                false, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				InMember, OptionalHelper, SrcManagedHandle);
		}
		else
		{
			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, new std::decay_t<T>(*InMember),
			                                                true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				InMember, OptionalHelper, SrcManagedHandle);
		}

		return MANAGED_HANDLE_TO_OBJECT(SrcManagedHandle);
	}

	static auto Get(const IManagedHandle InManagedHandle)
	{
		const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(InManagedHandle);

		return *static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>*>(SrcOptional->GetData());
	}
};
#endif
