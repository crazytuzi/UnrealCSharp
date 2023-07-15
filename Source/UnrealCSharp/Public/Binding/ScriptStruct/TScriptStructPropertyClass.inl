#pragma once

#include "Binding/Core/TPropertyClass.inl"
#include "Binding/ScriptStruct/TScriptStructName.inl"
#include "Binding/ScriptStruct/TScriptStructNameSpace.inl"

template <typename T>
struct TScriptStructPropertyClass
{
	static MonoClass* Get()
	{
		return FMonoDomain::Class_From_Name(TNameSpace<T, T>::Get()[0], TName<T, T>::Get());
	}
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FRotator>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FQuat>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FTransform>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FLinearColor>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FColor>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FPlane>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FVector>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FVector2D>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FVector4>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FRandomStream>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FGuid>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FBox2D>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FFallbackStruct>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FFloatRangeBound>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FFloatRange>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FInt32RangeBound>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FInt32Range>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FFloatInterval>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FInt32Interval>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FFrameNumber>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FFrameTime>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FSoftObjectPath>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FSoftClassPath>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FPrimaryAssetType>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FPrimaryAssetId>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FDateTime>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FPolyglotTextData>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FAssetBundleData>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FTestUninitializedScriptStructMembersTest>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FMatrix>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FIntPoint>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FTimespan>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};

template <typename T>
struct TPropertyClass<T, typename TEnableIf<TIsSame<T, FAssetBundleEntry>::Value, T>::Type> :
	TScriptStructPropertyClass<T>
{
};
