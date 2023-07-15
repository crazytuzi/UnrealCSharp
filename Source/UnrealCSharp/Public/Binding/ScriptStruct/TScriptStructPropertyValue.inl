#pragma once

#include "Binding/Core/TPropertyValue.inl"
#include "Binding/ScriptStruct/TScriptStructPropertyClass.inl"

template <typename T>
struct TScriptStructPropertyValue
{
	static MonoObject* Get(T* InMember, const bool bNeedFree = false)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(nullptr, InMember);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = TPropertyClass<T, T>::Get();

			auto InParams = static_cast<void*>(FoundMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
				FoundMonoClass, TGetArrayLength(InParams), &InParams);

			FCSharpEnvironment::GetEnvironment().Bind(T::StaticStruct(), false);

			FCSharpEnvironment::GetEnvironment().AddStructReference(T::StaticStruct(), nullptr,
			                                                        InMember, SrcMonoObject, bNeedFree);
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
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FRotator>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FQuat>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FTransform>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FLinearColor>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FColor>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FPlane>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FVector>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FVector2D>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FVector4>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FRandomStream>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FGuid>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FBox2D>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FFallbackStruct>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FFloatRangeBound>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FFloatRange>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FInt32RangeBound>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FInt32Range>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FFloatInterval>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FInt32Interval>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FFrameNumber>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FFrameTime>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FSoftObjectPath>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FSoftClassPath>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FPrimaryAssetType>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FPrimaryAssetId>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FDateTime>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FPolyglotTextData>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FAssetBundleData>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FTestUninitializedScriptStructMembersTest>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FMatrix>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FIntPoint>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FTimespan>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};

template <typename T>
struct TPropertyValue<T, typename TEnableIf<TIsSame<T, FAssetBundleEntry>::Value, T>::Type> :
	TScriptStructPropertyValue<T>
{
};
