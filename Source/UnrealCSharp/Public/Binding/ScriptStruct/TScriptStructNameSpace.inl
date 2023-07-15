#pragma once

#include "TScriptStruct.inl"
#include "Binding/TypeInfo/TNameSpace.inl"

template <typename T>
struct TScriptStructNameSpace
{
	static TArray<FString> Get()
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TScriptStruct<T>::Get())};
	}
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FRotator>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FQuat>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FTransform>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FLinearColor>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FColor>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FPlane>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FVector>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FVector2D>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FVector4>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FRandomStream>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FGuid>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FBox2D>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FFallbackStruct>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FFloatRangeBound>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FFloatRange>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FInt32RangeBound>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FInt32Range>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FFloatInterval>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FInt32Interval>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FFrameNumber>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FFrameTime>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FSoftObjectPath>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FSoftClassPath>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FPrimaryAssetType>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FPrimaryAssetId>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FDateTime>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FPolyglotTextData>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FAssetBundleData>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FTestUninitializedScriptStructMembersTest>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FMatrix>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FIntPoint>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FTimespan>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};

template <typename T>
struct TNameSpace<T, typename TEnableIf<TIsSame<T, FAssetBundleEntry>::Value, T>::Type> final :
	TScriptStructNameSpace<T>
{
};
