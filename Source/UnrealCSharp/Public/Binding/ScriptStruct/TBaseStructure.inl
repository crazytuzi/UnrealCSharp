#pragma once

#include "Macro/BindingMacro.h"
#include "UEVersion.h"

static UScriptStruct* StaticGetBaseStructureInternal(const FName& Name)
{
	static auto CoreUObjectPkg = FindObjectChecked<UPackage>(nullptr, TEXT("/Script/CoreUObject"));

	const auto Result = static_cast<UScriptStruct*>(StaticFindObjectFast(
#if UE_STATIC_FIND_OBJECT_FAST_ANY_PACKAGE
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name, false, false, RF_NoFlags, EInternalObjectFlags::None));
#else
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name, false, RF_NoFlags, EInternalObjectFlags::None));
#endif

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (Result == nullptr)
	{
		UE_LOG(LogClass, Fatal, TEXT("Failed to find native struct '%s.%s'"), *CoreUObjectPkg->GetName(),
		       *Name.ToString());
	}
#endif

	return Result;
}

#if UE_T_BASE_STRUCTURE_F_INT_POINT
template <>
struct TBaseStructure<FIntPoint>
{
	static UScriptStruct* Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FIntPoint));
	}
};
#endif

template <>
struct TBaseStructure<FTimespan>
{
	static UScriptStruct* Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FTimespan));
	}
};

template <>
struct TBaseStructure<FAssetBundleEntry>
{
	static UScriptStruct* Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FAssetBundleEntry));
	}
};

template <>
struct TBaseStructure<FBox>
{
	static UScriptStruct* Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FBox));
	}
};
