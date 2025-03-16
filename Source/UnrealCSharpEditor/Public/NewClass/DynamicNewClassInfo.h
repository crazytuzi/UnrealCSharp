#pragma once

#include "AddToProjectConfig.h"

struct FDynamicNewClassInfo
{
	FDynamicNewClassInfo(const FNewClassInfo& InNewClassInfo);

	FText GetClassName() const;

	FString GetClassNameCPP() const;

	FText GetClassDescription(const bool bFullDescription = true) const;

	bool IsSet() const;

	FNewClassInfo::EClassType ClassType;

	const UClass* BaseClass;
};
