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
#include "Template/TIsTSubclassOf.inl"
#include "Template/TIsTSet.inl"
#include "Template/TIsTMap.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsNotUEnum.inl"
#include "Template/TIsTEnumAsByte.inl"

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
struct TSinglePropertyValue
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
			TPropertyClass<T, T>::Get(), InMember);
	}

	static T Set(MonoObject* InValue)
	{
		return *(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue);
	}
};

template <typename T>
struct TMultiPropertyValue
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<std::decay_t<T>>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<std::decay_t<T>>(
				SrcMonoObject, InMember,
				!InGarbageCollectionHandle.IsValid() && !TTypeInfo<T>::IsReference() && bNeedFree);
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return *(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetMulti<std::decay_t<T>>(InValue);
	}
};

template <typename T>
struct TBindingPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetBinding(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddBindingReference(
					InGarbageCollectionHandle, SrcMonoObject, InMember);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddBindingReference(
					SrcMonoObject, InMember,
					!TTypeInfo<T>::IsReference() && bNeedFree);
			}
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return *FCSharpEnvironment::GetEnvironment().GetBinding<std::decay_t<T>>(InValue);
	}
};

template <typename T>
struct TBindingPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetBinding(*InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddBindingReference(
					InGarbageCollectionHandle, SrcMonoObject, *InMember);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddBindingReference(
					SrcMonoObject, *InMember, false);
			}
		}

		return SrcMonoObject;
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetBinding<
			std::remove_pointer_t<std::remove_reference_t<T>>>(InValue);
	}
};

template <typename T>
struct TScriptStructPropertyValue<T, std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(
			TBaseStructure<std::decay_t<T>>::Get(), InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().Bind(TBaseStructure<std::decay_t<T>>::Get(), false);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(InGarbageCollectionHandle,
				                                                        TBaseStructure<std::decay_t<T>>::Get(),
				                                                        InMember,
				                                                        SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<std::decay_t<T>>::Get(),
				                                                        InMember,
				                                                        SrcMonoObject,
				                                                        bNeedFree);
			}
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return *(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetStruct(InValue);
	}
};

template <typename T>
struct TScriptStructPropertyValue<T, std::enable_if_t<std::is_pointer_v<std::remove_reference_t<T>>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(
			TBaseStructure<std::remove_pointer_t<T>>::Get(), *InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().Bind(TBaseStructure<std::remove_pointer_t<T>>::Get(), false);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(InGarbageCollectionHandle,
				                                                        TBaseStructure<std::remove_pointer_t<T>>::Get(),
				                                                        *InMember,
				                                                        SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<std::remove_pointer_t<T>>::Get(),
				                                                        *InMember,
				                                                        SrcMonoObject,
				                                                        false);
			}
		}

		return SrcMonoObject;
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		return (std::decay_t<T>)FCSharpEnvironment::GetEnvironment().GetStruct(InValue);
	}
};

template <typename T>
struct TBindingEnumPropertyValue :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>> :
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T,
                      std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>> &&
                                       !std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(*InMember);
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<std::remove_pointer_t<std::decay_t<T>>>(InValue);
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTObjectPtr<T>::Value, T>>
{
	static MonoObject* Get(T* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(*InMember);
	}

	static T Set(const MonoObject* InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<typename T::ElementType*>(InValue);
	}
};
#endif

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*InMember->ToString())));

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(FoundMonoClass, 1, &NewMonoString);
	}

	static std::decay_t<T> Set(MonoObject* InValue)
	{
		return std::decay_t<T>(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InValue, nullptr))));
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(std::decay_t<T>::StaticStruct(), InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().Bind(std::decay_t<T>::StaticStruct(), false);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(
					InGarbageCollectionHandle, std::decay_t<T>::StaticStruct(), InMember, SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(
					std::decay_t<T>::StaticStruct(), InMember, SrcMonoObject,
					!TTypeInfo<T>::IsReference() && bNeedFree);
			}
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return *(std::decay_t<T>*)FCSharpEnvironment::GetEnvironment().GetStruct(InValue);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(InMember->operator*())));

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(FoundMonoClass, 1, &NewMonoString);
	}

	static std::decay_t<T> Set(MonoObject* InValue)
	{
		return std::decay_t<T>(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InValue, nullptr))));
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*InMember->ToString())));

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(FoundMonoClass, 1, &NewMonoString);
	}

	static std::decay_t<T> Set(MonoObject* InValue)
	{
		return std::decay_t<T>::FromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InValue, nullptr))));
	}
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
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FMapHelper>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			const auto FoundKeyPropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
				::Get();

			const auto FoundKeyPropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
				FoundKeyPropertyMonoClass);

			const auto FoundKeyPropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundKeyPropertyMonoType);

			const auto FoundValuePropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
				::Get();

			const auto FoundValuePropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Class_Get_Type(FoundValuePropertyMonoClass);

			const auto FoundValuePropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundValuePropertyMonoType);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			const auto KeyProperty = FTypeBridge::Factory(FoundKeyPropertyReflectionType, nullptr, "",
			                                              EObjectFlags::RF_Transient);

			KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			const auto ValueProperty = FTypeBridge::Factory(FoundValuePropertyReflectionType, nullptr, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty, InMember,
			                                      !InGarbageCollectionHandle.IsValid());

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddContainerReference(
					InGarbageCollectionHandle, InMember, MapHelper, SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddContainerReference(InMember, MapHelper, SrcMonoObject);
			}
		}

		return SrcMonoObject;
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		std::decay_t<T> Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InValue);

		for (auto Index = 0; Index < SrcContainer->GetMaxIndex(); ++Index)
		{
			if (SrcContainer->IsValidIndex(Index))
			{
				Value.Add(*static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>*>
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
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			const auto FoundPropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
				::Get();

			const auto FoundPropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
				FoundPropertyMonoClass);

			const auto FoundPropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundPropertyMonoType);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			const auto Property = FTypeBridge::Factory(FoundPropertyReflectionType, nullptr, "",
			                                           EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			const auto SetHelper = new FSetHelper(Property, InMember, !InGarbageCollectionHandle.IsValid());

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddContainerReference(
					InGarbageCollectionHandle, InMember, SetHelper, SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddContainerReference(InMember, SetHelper, SrcMonoObject);
			}
		}

		return SrcMonoObject;
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		std::decay_t<T> Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InValue);

		for (auto Index = 0; Index < SrcContainer->GetMaxIndex(); ++Index)
		{
			if (SrcContainer->IsValidIndex(Index))
			{
				Value.Add(
					*static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>*>(SrcContainer->
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
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::remove_pointer_t<std::decay_t<T>>, UClass>, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(FoundMonoClass);

		auto SubclassOf = new TSubclassOf<UObject>(*InMember);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(
			SrcMonoObject, SubclassOf, true);

		return SrcMonoObject;
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InValue)->Get();
	}
};


template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>
{
	static MonoObject* Get(std::decay_t<T>* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero(),
	                       bool bNeedFree = true)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			const auto FoundPropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
					typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
				::Get();

			const auto FoundPropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
				FoundPropertyMonoClass);

			const auto FoundPropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundPropertyMonoType);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			const auto Property = FTypeBridge::Factory(FoundPropertyReflectionType, nullptr, "",
			                                           EObjectFlags::RF_Transient);

			Property->SetPropertyFlags(CPF_HasGetValueTypeHash);

			const auto ArrayHelper = new FArrayHelper(Property, InMember, !InGarbageCollectionHandle.IsValid());

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddContainerReference(
					InGarbageCollectionHandle, InMember, ArrayHelper, SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddContainerReference(InMember, ArrayHelper, SrcMonoObject);
			}
		}

		return SrcMonoObject;
	}

	static std::decay_t<T> Set(const MonoObject* InValue)
	{
		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InValue);

		return std::decay_t<T>(
			static_cast<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>*>
			(SrcContainer->GetScriptArray()->GetData()),
			SrcContainer->Num());
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>> :
	TSinglePropertyValue<T>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
			TPropertyClass<T, T>::Get(), InMember);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>> :
	TSinglePropertyValue<T>
{
	static MonoObject* Get(std::decay_t<T>* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
			TPropertyClass<T, T>::Get(), InMember);
	}
};

template <typename T>
struct TPropertyValue<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TMultiPropertyValue<T>
{
};
