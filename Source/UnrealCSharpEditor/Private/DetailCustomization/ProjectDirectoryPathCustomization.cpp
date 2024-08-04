#include "DetailCustomization/ProjectDirectoryPathCustomization.h"

TSharedRef<IPropertyTypeCustomization> FProjectDirectoryPathCustomization::MakeInstance()
{
	return MakeShareable(
		new FProjectDirectoryPathCustomization(FPaths::ConvertRelativePathToFull(FPaths::ProjectDir())));
}
