#pragma once

#include "Macro/BindingMacro.h"

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

template <>
struct TBaseStructure<FIntPoint>
{
	static UScriptStruct* Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FIntPoint));
	}
};

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
