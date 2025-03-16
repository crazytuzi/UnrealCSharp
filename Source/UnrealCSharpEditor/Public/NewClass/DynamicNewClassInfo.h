#pragma once

#include "AddToProjectConfig.h"

struct FDynamicNewClassInfo : FNewClassInfo
{
	using FNewClassInfo::FNewClassInfo;

	explicit FDynamicNewClassInfo(const FNewClassInfo& InNewClassInfo);

	FText GetClassName() const;

	FText GetClassDescription(const bool bFullDescription = true) const;

	FString GetClassNameCPP() const;
};
