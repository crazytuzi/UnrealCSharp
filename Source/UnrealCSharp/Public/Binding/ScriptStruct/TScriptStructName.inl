#pragma once

#include "Binding/TypeInfo/TName.inl"

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FRotator>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Rotator");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FQuat>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Quat");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FTransform>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Transform");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FLinearColor>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("LinearColor");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FColor>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Color");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FPlane>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Plane");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FVector>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Vector");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FVector2D>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Vector2D");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FVector4>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Vector4");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FRandomStream>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("RandomStream");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FGuid>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Guid");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FBox2D>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Box2D");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FFallbackStruct>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("FallbackStruct");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FFloatRangeBound>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("FloatRangeBound");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FFloatRange>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("FloatRange");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FInt32RangeBound>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Int32RangeBound");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FInt32Range>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Int32Range");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FFloatInterval>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("FloatInterval");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FInt32Interval>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Int32Interval");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FFrameNumber>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("FrameNumber");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FFrameTime>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("FrameTime");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FSoftObjectPath>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("SoftObjectPath");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FSoftClassPath>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("SoftClassPath");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FPrimaryAssetType>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("PrimaryAssetType");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FPrimaryAssetId>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("PrimaryAssetId");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FDateTime>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("DateTime");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FPolyglotTextData>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("PolyglotTextData");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FAssetBundleData>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("AssetBundleData");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FTestUninitializedScriptStructMembersTest>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("TestUninitializedScriptStructMembersTest");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FMatrix>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Matrix");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FIntPoint>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("IntPoint");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FTimespan>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("Timespan");
	}
};

template <typename T>
struct TName<T, typename TEnableIf<TIsSame<T, FAssetBundleEntry>::Value, T>::Type>
{
	static FString Get()
	{
		return TEXT("AssetBundleEntry");
	}
};
