#include "DetailCustomization/GameContentDirectoryPathCustomization.h"

TSharedRef<IPropertyTypeCustomization> FGameContentDirectoryPathCustomization::MakeInstance()
{
	return MakeShareable(
		new FGameContentDirectoryPathCustomization(FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir())));
}
