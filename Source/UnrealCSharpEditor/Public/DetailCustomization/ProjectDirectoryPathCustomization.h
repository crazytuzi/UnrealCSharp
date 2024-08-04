#pragma once

#include "DirectoryPathCustomization.h"

class FProjectDirectoryPathCustomization final : public FDirectoryPathCustomization
{
public:
	using FDirectoryPathCustomization::FDirectoryPathCustomization;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
};
