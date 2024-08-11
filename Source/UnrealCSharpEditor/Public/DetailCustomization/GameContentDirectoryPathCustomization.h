#pragma once

#include "DirectoryPathCustomization.h"

class FGameContentDirectoryPathCustomization final : public FDirectoryPathCustomization
{
public:
	using FDirectoryPathCustomization::FDirectoryPathCustomization;

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
};
