#pragma once

#include "Binding/Template/TClassName.inl"
#include "Binding/ScriptStruct/TScriptStructName.inl"

template <typename T>
struct TScriptStructClassName
{
	static FString Get()
	{
		return TName<T, T>::Get();
	}
};

template <>
struct TClassName<FRotator> :
	TScriptStructClassName<FRotator>
{
};

template <>
struct TClassName<FQuat> :
	TScriptStructClassName<FQuat>
{
};

template <>
struct TClassName<FTransform> :
	TScriptStructClassName<FTransform>
{
};

template <>
struct TClassName<FLinearColor> :
	TScriptStructClassName<FLinearColor>
{
};

template <>
struct TClassName<FColor> :
	TScriptStructClassName<FColor>
{
};

template <>
struct TClassName<FPlane> :
	TScriptStructClassName<FPlane>
{
};

template <>
struct TClassName<FVector> :
	TScriptStructClassName<FVector>
{
};

template <>
struct TClassName<FVector2D> :
	TScriptStructClassName<FVector2D>
{
};

template <>
struct TClassName<FVector4> :
	TScriptStructClassName<FVector4>
{
};

template <>
struct TClassName<FRandomStream> :
	TScriptStructClassName<FRandomStream>
{
};

template <>
struct TClassName<FGuid> :
	TScriptStructClassName<FGuid>
{
};

template <>
struct TClassName<FBox2D> :
	TScriptStructClassName<FBox2D>
{
};

template <>
struct TClassName<FFallbackStruct> :
	TScriptStructClassName<FFallbackStruct>
{
};

template <>
struct TClassName<FFloatRangeBound> :
	TScriptStructClassName<FFloatRangeBound>
{
};

template <>
struct TClassName<FFloatRange> :
	TScriptStructClassName<FFloatRange>
{
};

template <>
struct TClassName<FInt32RangeBound> :
	TScriptStructClassName<FInt32RangeBound>
{
};

template <>
struct TClassName<FInt32Range> :
	TScriptStructClassName<FInt32Range>
{
};

template <>
struct TClassName<FFloatInterval> :
	TScriptStructClassName<FFloatInterval>
{
};

template <>
struct TClassName<FInt32Interval> :
	TScriptStructClassName<FInt32Interval>
{
};

template <>
struct TClassName<FFrameNumber> :
	TScriptStructClassName<FFrameNumber>
{
};

template <>
struct TClassName<FFrameTime> :
	TScriptStructClassName<FFrameTime>
{
};

template <>
struct TClassName<FSoftObjectPath> :
	TScriptStructClassName<FSoftObjectPath>
{
};

template <>
struct TClassName<FSoftClassPath> :
	TScriptStructClassName<FSoftClassPath>
{
};

template <>
struct TClassName<FPrimaryAssetType> :
	TScriptStructClassName<FPrimaryAssetType>
{
};

template <>
struct TClassName<FPrimaryAssetId> :
	TScriptStructClassName<FPrimaryAssetId>
{
};

template <>
struct TClassName<FDateTime> :
	TScriptStructClassName<FDateTime>
{
};

template <>
struct TClassName<FPolyglotTextData> :
	TScriptStructClassName<FPolyglotTextData>
{
};

template <>
struct TClassName<FAssetBundleData> :
	TScriptStructClassName<FAssetBundleData>
{
};

template <>
struct TClassName<FTestUninitializedScriptStructMembersTest> :
	TScriptStructClassName<FTestUninitializedScriptStructMembersTest>
{
};

template <>
struct TClassName<FMatrix> :
	TScriptStructClassName<FMatrix>
{
};

template <>
struct TClassName<FIntPoint> :
	TScriptStructClassName<FIntPoint>
{
};

template <>
struct TClassName<FTimespan> :
	TScriptStructClassName<FTimespan>
{
};

template <>
struct TClassName<FAssetBundleEntry> :
	TScriptStructClassName<FAssetBundleEntry>
{
};
