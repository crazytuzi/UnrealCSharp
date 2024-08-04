#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

class FDirectoryPathCustomization : public IPropertyTypeCustomization
{
public:
	explicit FDirectoryPathCustomization(const FString& InAbsoluteDirectory);

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle,
	                             class FDetailWidgetRow& HeaderRow,
	                             IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle,
	                               class IDetailChildrenBuilder& StructBuilder,
	                               IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	/** Delegate used to display a directory picker */
	FReply OnPickDirectory(TSharedRef<IPropertyHandle> PropertyHandle, const bool bUseRelativePath) const;

	/** Check whether that the chosen path is valid */
	bool IsValidPath(const FString& AbsolutePath, const bool bUseRelativePath,
	                 FText* const OutReason = nullptr) const;

	/** The browse button widget */
	TSharedPtr<SButton> BrowseButton;

	/** Absolute path to the directory */
	FString AbsoluteDirectory;
};
