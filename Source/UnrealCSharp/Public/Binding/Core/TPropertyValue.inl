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

template <typename T, typename Enable = void>
struct TBindingPropertyValue
{
};

template <typename T, typename Enable = void>
struct TScriptStructPropertyValue
{
};

template <typename T>
struct TPrimitivePropertyValue
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
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
struct TStringPropertyValue
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetStringObject<std::decay_t<T>>(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddStringReference<std::decay_t<T>, false, true>(
				FoundClass, SrcObject, InMember);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStringReference<std::decay_t<T>, false, false>(
				FoundClass, SrcObject, InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStringReference<std::decay_t<T>, true, false>(
				FoundClass, SrcObject, new std::decay_t<T>(*InMember));
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		return std::decay_t<T>(*FCSharpEnvironment::GetEnvironment().GetString<std::decay_t<T>>(InValue));
	}
};

template <typename T>
struct TMultiPropertyValue
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<std::decay_t<T>>(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>, false, true>(
				FoundClass, SrcObject, InMember);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>, false, false>(
				FoundClass, SrcObject, InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>, true, false>(
				FoundClass, SrcObject, new std::decay_t<T>(*InMember));
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue) -> T
	{
		return *(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetMulti<std::decay_t<T>>(InValue);
	}
};

template <typename T>
struct TBindingPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetBinding(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddBindingReference(
				InGarbageCollectionHandle, FoundClass, SrcObject, InMember);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, false>(
				FoundClass, SrcObject, InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, true>(
				FoundClass, SrcObject, new std::decay_t<T>(*InMember));
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue) -> T
	{
		return *FCSharpEnvironment::GetEnvironment().GetBinding<std::decay_t<T>>(InValue);
	}
};

template <typename T>
struct TBindingPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetBinding(*InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddBindingReference(
				InGarbageCollectionHandle, FoundClass, SrcObject, *InMember);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, false>(
				SrcObject, InMember);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<std::decay_t<T>, true>(
				SrcObject, new std::decay_t<T>(*InMember));
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue) -> std::decay_t<T>
	{
		return FCSharpEnvironment::GetEnvironment().GetBinding<
			std::remove_pointer_t<std::remove_reference_t<T>>>(InValue);
	}
};

template <typename T>
struct TScriptStructPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(
			TBaseStructure<std::decay_t<T>>::Get(), InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().Bind<false>(TBaseStructure<std::decay_t<T>>::Get());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InGarbageCollectionHandle, TBaseStructure<std::decay_t<T>>::Get(), InMember, SrcObject);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		FCSharpEnvironment::GetEnvironment().Bind<false>(TBaseStructure<std::decay_t<T>>::Get());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				TBaseStructure<std::decay_t<T>>::Get(), InMember, SrcObject);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				TBaseStructure<std::decay_t<T>>::Get(), new std::decay_t<T>(*InMember), SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue) -> T
	{
		return *FCSharpEnvironment::GetEnvironment().GetStruct<std::decay_t<T>>(InValue);
	}
};

template <typename T>
struct TScriptStructPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(
			TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(), *InMember);

		if (SrcObject == nullptr)
		{
			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().Bind<false>(
				TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InGarbageCollectionHandle, TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(),
				*InMember, SrcObject, false);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		FCSharpEnvironment::GetEnvironment().Bind<false>(
			TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(), InMember,
				SrcObject);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				TBaseStructure<std::decay_t<std::remove_pointer_t<T>>>::Get(), new std::decay_t<T>(*InMember),
				SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetStruct<std::decay_t<std::remove_pointer_t<T>>>(InValue);
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
struct TPropertyValue<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(
			std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<std::decay_t<T>>>>(*InMember));
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(
			std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<std::decay_t<T>>>>(*InMember));
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<std::remove_pointer_t<std::decay_t<T>>>(InValue);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>>
{
	static auto Get(T* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(*InMember);
	}

	template <auto IsReference>
	static auto Get(T* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(*InMember);
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<typename T::ElementType>(InValue);
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
                                          !std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(std::decay_t<T>::StaticStruct(), InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().Bind<false>(std::decay_t<T>::StaticStruct());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InGarbageCollectionHandle, std::decay_t<T>::StaticStruct(), InMember, SrcObject);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		FCSharpEnvironment::GetEnvironment().Bind<false>(std::decay_t<T>::StaticStruct());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				std::decay_t<T>::StaticStruct(), InMember, SrcObject);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				std::decay_t<T>::StaticStruct(), new std::decay_t<T>(*InMember), SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue) -> T
	{
		return *FCSharpEnvironment::GetEnvironment().GetStruct<std::decay_t<T>>(InValue);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsUStruct<std::remove_pointer_t<std::decay_t<T>>>::Value &&
                                          std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(
			std::remove_pointer_t<std::decay_t<T>>::StaticStruct(), *InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			SrcObject = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().Bind<false>(std::remove_pointer_t<std::decay_t<T>>::StaticStruct());

			FCSharpEnvironment::GetEnvironment().AddStructReference(
				InGarbageCollectionHandle, std::remove_pointer_t<std::decay_t<T>>::StaticStruct(), *InMember,
				SrcObject);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		auto SrcObject = FoundClass->NewObject();

		FCSharpEnvironment::GetEnvironment().Bind<false>(std::remove_pointer_t<std::decay_t<T>>::StaticStruct());

		if constexpr (IsReference)
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<false>(
				std::remove_pointer_t<std::decay_t<T>>::StaticStruct(), *InMember, SrcObject);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				std::remove_pointer_t<std::decay_t<T>>::StaticStruct(),
				new std::remove_pointer_t<std::decay_t<T>>(**InMember), SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue) -> T
	{
		return FCSharpEnvironment::GetEnvironment().GetStruct<std::remove_pointer_t<std::decay_t<T>>>(InValue);
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
struct TPropertyValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FMapHelper>(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto KeyProperty = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                                nullptr, "", EObjectFlags::RF_Transient);

			KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			const auto ValueProperty = FTypeBridge::Factory<>(
				FoundClass->GetGenericArgument(1), nullptr, "", EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			SrcObject = FoundClass->NewObject();

			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty,
			                                      InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				InGarbageCollectionHandle, InMember, MapHelper, FoundClass, SrcObject);
		}

		return SrcObject;
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

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty,
			                                      InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				MapHelper, FoundClass, SrcObject);
		}
		else
		{
			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty,
			                                      new std::decay_t<T>(*InMember), true, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				MapHelper, FoundClass, SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		std::decay_t<T> Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InValue);

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
struct TPropertyValue<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                             nullptr, "", EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			SrcObject = FoundClass->NewObject();

			const auto SetHelper = new FSetHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				InGarbageCollectionHandle, InMember, SetHelper, FoundClass, SrcObject);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(), nullptr,
		                                             "", EObjectFlags::RF_Transient);

		Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto SetHelper = new FSetHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				SetHelper, FoundClass, SrcObject);
		}
		else
		{
			const auto SetHelper = new FSetHelper(Property, new std::decay_t<T>(*InMember), true, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				SetHelper, FoundClass, SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		std::decay_t<T> Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InValue);

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
struct TPropertyValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                             nullptr, "", EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			SrcObject = FoundClass->NewObject();

			const auto ArrayHelper = new FArrayHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				InGarbageCollectionHandle, InMember, ArrayHelper, FoundClass, SrcObject);
		}

		return SrcObject;
	}

	template <auto IsReference>
	static auto Get(std::decay_t<T>* InMember)
	{
		const auto FoundClass = TPropertyClass<T, T>::Get();

		const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(), nullptr,
		                                             "", EObjectFlags::RF_Transient);

		Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto ArrayHelper = new FArrayHelper(Property, InMember, false, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, FoundClass, SrcObject);
		}
		else
		{
			const auto ArrayHelper = new FArrayHelper(Property, new std::decay_t<T>(*InMember), true, true);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, FoundClass, SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InValue);

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
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
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
struct TPropertyValue<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TPrimitivePropertyValue<T>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
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
struct TPropertyValue<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>>
{
	static auto Get(std::decay_t<T>* InMember, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		auto SrcObject = FCSharpEnvironment::GetEnvironment().GetOptionalObject<FOptionalHelper>(InMember);

		if (SrcObject == nullptr)
		{
			const auto FoundClass = TPropertyClass<T, T>::Get();

			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto Property = FTypeBridge::Factory<>(FoundClass->GetGenericArgument(),
			                                             nullptr, "", EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(Property);

			SrcObject = FoundClass->NewObject();

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, InMember,
			                                                false, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, true>(
				InMember, OptionalHelper, SrcObject);
		}

		return SrcObject;
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

		auto SrcObject = FoundClass->NewObject();

		if constexpr (IsReference)
		{
			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, InMember,
			                                                false, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				InMember, OptionalHelper, SrcObject);
		}
		else
		{
			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, new std::decay_t<T>(*InMember),
			                                                true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				InMember, OptionalHelper, SrcObject);
		}

		return SrcObject;
	}

	static auto Set(const FGarbageCollectionHandle InValue)
	{
		const auto SrcOptional = FCSharpEnvironment::GetEnvironment().GetOptional(InValue);

		return *static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<>*>(SrcOptional->GetData());
	}
};
#endif
