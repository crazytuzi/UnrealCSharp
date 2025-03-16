#pragma once

#include "AddToProjectConfig.h"

struct FDynamicNewClassInfo : FNewClassInfo
{
	typedef FNewClassInfo Super;

	using Super::Super;

	explicit FDynamicNewClassInfo(const Super& InSuper);

	FText GetClassName() const;

	FText GetClassDescription(const bool bFullDescription = true) const;

	FString GetClassNameCPP() const;
};
