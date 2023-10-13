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
#include "UEVersion.h"

template <typename T, typename Enable = void>
struct TPropertyValue
{
};

template <typename T>
struct TSinglePropertyValue
{
	static MonoObject* Get(T* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
			TPropertyClass<T, T>::Get(), InMember);
	}

	static T Set(MonoObject* InValue)
	{
		return *(T*)FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue);
	}
};

template <typename T>
struct TMultiPropertyValue
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<T>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<T>(
				SrcMonoObject, InMember, !InGarbageCollectionHandle.IsValid());
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return *(T*)FCSharpEnvironment::GetEnvironment().GetMulti<T>(InValue);
	}
};

template <typename T>
struct TBindingPropertyValue
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetBinding(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			auto InParams = static_cast<void*>(FoundMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), &InParams);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddBindingReference(
					InGarbageCollectionHandle, SrcMonoObject, InMember);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddBindingReference(SrcMonoObject, InMember);
			}
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return *FCSharpEnvironment::GetEnvironment().GetBinding<T>(InValue);
	}
};

template <typename T>
struct TScriptStructPropertyValue
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(TBaseStructure<T>::Get(), InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			auto InParams = static_cast<void*>(FoundMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), &InParams);

			FCSharpEnvironment::GetEnvironment().Bind(TBaseStructure<T>::Get(), false);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(InGarbageCollectionHandle,
				                                                        TBaseStructure<T>::Get(), InMember,
				                                                        SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<T>::Get(), InMember,
				                                                        SrcMonoObject);
			}
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct(InValue);

		T Value;

		TBaseStructure<T>::Get()->CopyScriptStruct(&Value, SrcStruct);

		return Value;
	}
};

template <typename T>
struct TBindingEnumPropertyValue :
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, uint8>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, uint16>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, uint32>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, uint64>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, int8>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, int16>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, int32>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, int64>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, bool>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, float>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T,
                      typename TEnableIf<TAnd<
	                                         TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                         TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                      ::Type>
#else
struct TPropertyValue<T,
                      typename TEnableIf<TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>::Value &&
                                         !std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>
                      ::Type>
#endif
{
	static MonoObject* Get(T* InMember)
	{
		return FCSharpEnvironment::GetEnvironment().Bind(*InMember);
	}

	static T Set(const MonoObject* InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetObject<typename TRemovePointer<T>::Type>(InValue);
	}
};

#if UE_OBJECT_PTR
template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsTObjectPtr<T>::Value, T>::Type>
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
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, FName>, T>::Type>
#endif
{
	static MonoObject* Get(T* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*InMember->ToString())));

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass, 1, &NewMonoString);
	}

	static T Set(MonoObject* InValue)
	{
		return T(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InValue, nullptr))));
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(T::StaticStruct(), InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			auto InParams = static_cast<void*>(FoundMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), &InParams);

			FCSharpEnvironment::GetEnvironment().Bind(T::StaticStruct(), false);

			if (InGarbageCollectionHandle.IsValid())
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(InGarbageCollectionHandle, T::StaticStruct(),
				                                                        InMember, SrcMonoObject);
			}
			else
			{
				FCSharpEnvironment::GetEnvironment().AddStructReference(T::StaticStruct(), InMember, SrcMonoObject);
			}
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct(InValue);

		T Value;

		T::StaticStruct()->CopyScriptStruct(&Value, SrcStruct);

		return Value;
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, FString>, T>::Type>
#endif
{
	static MonoObject* Get(T* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(InMember->operator*())));

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass, 1, &NewMonoString);
	}

	static T Set(MonoObject* InValue)
	{
		return T(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InValue, nullptr))));
	}
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, FText>, T>::Type>
#endif
{
	static MonoObject* Get(T* InMember)
	{
		const auto FoundMonoClass = TPropertyClass<T, T>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*InMember->ToString())));

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass, 1, &NewMonoString);
	}

	static T Set(MonoObject* InValue)
	{
		return T::FromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InValue, nullptr))));
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTSoftObjectPtr<T>::Value, T>::Type> :
	TMultiPropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type> :
#else
struct TPropertyValue<T, typename TEnableIf<std::is_same_v<T, double>, T>::Type> :
#endif
	TSinglePropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTMap<T>::Value, T>::Type>
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FMapHelper>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			const auto FoundKeyPropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<T>::template Type<0>,
					typename TTemplateTypeTraits<T>::template Type<0>>
				::Get();

			const auto FoundKeyPropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
				FoundKeyPropertyMonoClass);

			const auto FoundKeyPropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundKeyPropertyMonoType);

			const auto FoundValuePropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<T>::template Type<1>,
					typename TTemplateTypeTraits<T>::template Type<1>>
				::Get();

			const auto FoundValuePropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Class_Get_Type(FoundValuePropertyMonoClass);

			const auto FoundValuePropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundValuePropertyMonoType);

			void* InParams[2] = {FoundKeyPropertyReflectionType, FoundValuePropertyReflectionType};

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), InParams);

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

	static T Set(const MonoObject* InValue)
	{
		T Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InValue);

		for (auto Index = 0; Index < SrcContainer->GetMaxIndex(); ++Index)
		{
			if (SrcContainer->IsValidIndex(Index))
			{
				Value.Add(*static_cast<typename TTemplateTypeTraits<T>::template Type<0>*>
				          (SrcContainer->GetEnumeratorKey(Index)),
				          *static_cast<typename TTemplateTypeTraits<T>::template Type<1>*>
				          (SrcContainer->GetEnumeratorValue(Index)));
			}
		}

		return Value;
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTSet<T>::Value, T>::Type>
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			const auto FoundPropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<T>::template Type<0>,
					typename TTemplateTypeTraits<T>::template Type<0>>
				::Get();

			const auto FoundPropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
				FoundPropertyMonoClass);

			const auto FoundPropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundPropertyMonoType);

			auto InParams = static_cast<void*>(FoundPropertyMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), &InParams);

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

	static T Set(const MonoObject* InValue)
	{
		T Value;

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InValue);

		for (auto Index = 0; Index < SrcContainer->GetMaxIndex(); ++Index)
		{
			if (SrcContainer->IsValidIndex(Index))
			{
				Value.Add(
					*static_cast<typename TTemplateTypeTraits<T>::template Type<0>*>(SrcContainer->
						GetEnumerator(Index)));
			}
		}

		return Value;
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type> :
	TMultiPropertyValue<T>
{
};

template <typename T>
#if UE_T_IS_SAME
struct TPropertyValue<T,
                      typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type>
#else
struct TPropertyValue<T,
                      typename TEnableIf<std::is_same_v<typename TRemovePointer<T>::Type, UClass>, T>::Type>
#endif
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetMultiObject<TSubclassOf<UObject>>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>>(
				SrcMonoObject, InMember, !InGarbageCollectionHandle.IsValid());
		}

		return SrcMonoObject;
	}

	static T Set(const MonoObject* InValue)
	{
		return FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InValue)->Get();
	}
};


template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTArray<T>::Value, T>::Type>
{
	static MonoObject* Get(T* InMember,
	                       const FGarbageCollectionHandle& InGarbageCollectionHandle = FGarbageCollectionHandle::Zero())
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			const auto FoundPropertyMonoClass = TPropertyClass<
					typename TTemplateTypeTraits<T>::template Type<0>,
					typename TTemplateTypeTraits<T>::template Type<0>>
				::Get();

			const auto FoundPropertyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
				FoundPropertyMonoClass);

			const auto FoundPropertyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Type_Get_Object(FoundPropertyMonoType);

			auto InParams = static_cast<void*>(FoundPropertyMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), &InParams);

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

	static T Set(const MonoObject* InValue)
	{
		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InValue);

		return T(
			static_cast<typename TTemplateTypeTraits<T>::template Type<0>*>
			(SrcContainer->GetScriptArray()->GetData()),
			SrcContainer->Num());
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TAnd<TIsEnum<T>, TNot<TIsNotUEnum<T>>>::Value, T>::Type> :
	TSinglePropertyValue<T>
{
	static MonoObject* Get(T* InMember)
	{
		// @TODO
		T Value = *InMember;

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
			TPropertyClass<T, T>::Get(), &Value);
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTEnumAsByte<T>::Value, T>::Type> :
	TPropertyValue<typename T::EnumType, typename T::EnumType>
{
	static MonoObject* Get(T* InMember)
	{
		// @TODO
		T Value = *InMember;

		return FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
			TPropertyClass<T, T>::Get(), &Value);
	}
};

template <typename T>
struct TPropertyValue<T,
                      typename TEnableIf<TIsTSoftClassPtr<T>::Value, T>::Type> :
	TMultiPropertyValue<T>
{
};
