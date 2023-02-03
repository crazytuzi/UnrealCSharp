#pragma once

#include "TScriptStruct.inl"

template <class T>
struct TScriptStructName
{
	static FString Get() { return T::StaticStruct()->GetName(); }
};

template <>
struct TScriptStructName<FRotator>
{
	static FString Get() { return TEXT("Rotator"); }
};

template <>
struct TScriptStructName<FQuat>
{
	static FString Get() { return TEXT("Quat"); }
};

template <>
struct TScriptStructName<FTransform>
{
	static FString Get() { return TEXT("Transform"); }
};

template <>
struct TScriptStructName<FLinearColor>
{
	static FString Get() { return TEXT("LinearColor"); }
};

template <>
struct TScriptStructName<FColor>
{
	static FString Get() { return TEXT("Color"); }
};

template <>
struct TScriptStructName<FPlane>
{
	static FString Get() { return TEXT("Plane"); }
};

template <>
struct TScriptStructName<FVector>
{
	static FString Get() { return TEXT("Vector"); }
};

template <>
struct TScriptStructName<FVector2D>
{
	static FString Get() { return TEXT("Vector2D"); }
};

template <>
struct TScriptStructName<FVector4>
{
	static FString Get() { return TEXT("Vector4"); }
};

template <>
struct TScriptStructName<FRandomStream>
{
	static FString Get() { return TEXT("RandomStream"); }
};

template <>
struct TScriptStructName<FGuid>
{
	static FString Get() { return TEXT("Guid"); }
};

template <>
struct TScriptStructName<FBox2D>
{
	static FString Get() { return TEXT("Box2D"); }
};

template <>
struct TScriptStructName<FFallbackStruct>
{
	static FString Get() { return TEXT("FallbackStruct"); }
};

template <>
struct TScriptStructName<FFloatRangeBound>
{
	static FString Get() { return TEXT("FloatRangeBound"); }
};

template <>
struct TScriptStructName<FFloatRange>
{
	static FString Get() { return TEXT("FloatRange"); }
};

template <>
struct TScriptStructName<FInt32RangeBound>
{
	static FString Get() { return TEXT("Int32RangeBound"); }
};

template <>
struct TScriptStructName<FInt32Range>
{
	static FString Get() { return TEXT("Int32Range"); }
};

template <>
struct TScriptStructName<FFloatInterval>
{
	static FString Get() { return TEXT("FloatInterval"); }
};

template <>
struct TScriptStructName<FInt32Interval>
{
	static FString Get() { return TEXT("Int32Interval"); }
};

template <>
struct TScriptStructName<FFrameNumber>
{
	static FString Get() { return TEXT("FrameNumber"); }
};

template <>
struct TScriptStructName<FFrameTime>
{
	static FString Get() { return TEXT("FrameTime"); }
};

template <>
struct TScriptStructName<FSoftObjectPath>
{
	static FString Get() { return TEXT("SoftObjectPath"); }
};

template <>
struct TScriptStructName<FSoftClassPath>
{
	static FString Get() { return TEXT("SoftClassPath"); }
};

template <>
struct TScriptStructName<FPrimaryAssetType>
{
	static FString Get() { return TEXT("PrimaryAssetType"); }
};

template <>
struct TScriptStructName<FPrimaryAssetId>
{
	static FString Get() { return TEXT("PrimaryAssetId"); }
};

template <>
struct TScriptStructName<FDateTime>
{
	static FString Get() { return TEXT("DateTime"); }
};

template <>
struct TScriptStructName<FPolyglotTextData>
{
	static FString Get() { return TEXT("PolyglotTextData"); }
};

template <>
struct TScriptStructName<FAssetBundleData>
{
	static FString Get() { return TEXT("AssetBundleData"); }
};

template <>
struct TScriptStructName<FTestUninitializedScriptStructMembersTest>
{
	static FString Get() { return TEXT("TestUninitializedScriptStructMembersTest"); }
};

template <>
struct TScriptStructName<FMatrix>
{
	static FString Get() { return TEXT("Matrix"); }
};

template <>
struct TScriptStructName<FIntPoint>
{
	static FString Get() { return TEXT("IntPoint"); }
};

template <>
struct TScriptStructName<FTimespan>
{
	static FString Get() { return TEXT("Timespan"); }
};
