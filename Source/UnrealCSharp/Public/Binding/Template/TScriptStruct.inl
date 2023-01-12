#pragma once

static UScriptStruct* StaticGetBaseStructureInternal(const FName& Name)
{
	static auto CoreUObjectPkg = FindObjectChecked<UPackage>(nullptr, TEXT("/Script/CoreUObject"));

	const auto Result = static_cast<UScriptStruct*>(StaticFindObjectFast(
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name, false, false, RF_NoFlags, EInternalObjectFlags::None));

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (Result == nullptr)
	{
		UE_LOG(LogClass, Fatal, TEXT("Failed to find native struct '%s.%s'"), *CoreUObjectPkg->GetName(),
		       *Name.ToString());
	}
#endif

	return Result;
}

template <class T>
struct TScriptStruct
{
	static UScriptStruct* Get() { return T::StaticStruct(); }
};

template <>
struct TScriptStruct<FRotator>
{
	static UScriptStruct* Get() { return TBaseStructure<FRotator>::Get(); }
};

template <>
struct TScriptStruct<FQuat>
{
	static UScriptStruct* Get() { return TBaseStructure<FQuat>::Get(); }
};

template <>
struct TScriptStruct<FTransform>
{
	static UScriptStruct* Get() { return TBaseStructure<FTransform>::Get(); }
};

template <>
struct TScriptStruct<FLinearColor>
{
	static UScriptStruct* Get() { return TBaseStructure<FLinearColor>::Get(); }
};

template <>
struct TScriptStruct<FColor>
{
	static UScriptStruct* Get() { return TBaseStructure<FColor>::Get(); }
};

template <>
struct TScriptStruct<FPlane>
{
	static UScriptStruct* Get() { return TBaseStructure<FPlane>::Get(); }
};

template <>
struct TScriptStruct<FVector>
{
	static UScriptStruct* Get() { return TBaseStructure<FVector>::Get(); }
};

template <>
struct TScriptStruct<FVector2D>
{
	static UScriptStruct* Get() { return TBaseStructure<FVector2D>::Get(); }
};

template <>
struct TScriptStruct<FVector4>
{
	static UScriptStruct* Get() { return TBaseStructure<FVector4>::Get(); }
};

template <>
struct TScriptStruct<FRandomStream>
{
	static UScriptStruct* Get() { return TBaseStructure<FRandomStream>::Get(); }
};

template <>
struct TScriptStruct<FGuid>
{
	static UScriptStruct* Get() { return TBaseStructure<FGuid>::Get(); }
};

template <>
struct TScriptStruct<FBox2D>
{
	static UScriptStruct* Get() { return TBaseStructure<FBox2D>::Get(); }
};

template <>
struct TScriptStruct<FFallbackStruct>
{
	static UScriptStruct* Get() { return TBaseStructure<FFallbackStruct>::Get(); }
};

template <>
struct TScriptStruct<FFloatRangeBound>
{
	static UScriptStruct* Get() { return TBaseStructure<FFloatRangeBound>::Get(); }
};

template <>
struct TScriptStruct<FFloatRange>
{
	static UScriptStruct* Get() { return TBaseStructure<FFloatRange>::Get(); }
};

template <>
struct TScriptStruct<FInt32RangeBound>
{
	static UScriptStruct* Get() { return TBaseStructure<FInt32RangeBound>::Get(); }
};

template <>
struct TScriptStruct<FInt32Range>
{
	static UScriptStruct* Get() { return TBaseStructure<FInt32Range>::Get(); }
};

template <>
struct TScriptStruct<FFloatInterval>
{
	static UScriptStruct* Get() { return TBaseStructure<FFloatInterval>::Get(); }
};

template <>
struct TScriptStruct<FInt32Interval>
{
	static UScriptStruct* Get() { return TBaseStructure<FInt32Interval>::Get(); }
};

template <>
struct TScriptStruct<FFrameNumber>
{
	static UScriptStruct* Get() { return TBaseStructure<FFrameNumber>::Get(); }
};

template <>
struct TScriptStruct<FFrameTime>
{
	static UScriptStruct* Get() { return TBaseStructure<FFrameTime>::Get(); }
};

template <>
struct TScriptStruct<FSoftObjectPath>
{
	static UScriptStruct* Get() { return TBaseStructure<FSoftObjectPath>::Get(); }
};

template <>
struct TScriptStruct<FSoftClassPath>
{
	static UScriptStruct* Get() { return TBaseStructure<FSoftClassPath>::Get(); }
};

template <>
struct TScriptStruct<FPrimaryAssetType>
{
	static UScriptStruct* Get() { return TBaseStructure<FPrimaryAssetType>::Get(); }
};

template <>
struct TScriptStruct<FPrimaryAssetId>
{
	static UScriptStruct* Get() { return TBaseStructure<FPrimaryAssetId>::Get(); }
};

template <>
struct TScriptStruct<FDateTime>
{
	static UScriptStruct* Get() { return TBaseStructure<FDateTime>::Get(); }
};

template <>
struct TScriptStruct<FPolyglotTextData>
{
	static UScriptStruct* Get() { return TBaseStructure<FPolyglotTextData>::Get(); }
};

template <>
struct TScriptStruct<FAssetBundleData>
{
	static UScriptStruct* Get() { return TBaseStructure<FAssetBundleData>::Get(); }
};

template <>
struct TScriptStruct<FTestUninitializedScriptStructMembersTest>
{
	static UScriptStruct* Get() { return TBaseStructure<FTestUninitializedScriptStructMembersTest>::Get(); }
};
