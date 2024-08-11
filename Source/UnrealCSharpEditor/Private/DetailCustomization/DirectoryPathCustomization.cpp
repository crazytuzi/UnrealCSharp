#include "DetailCustomization/DirectoryPathCustomization.h"
#include "Misc/MessageDialog.h"
#include "Modules/ModuleManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Images/SImage.h"
#include "EditorDirectories.h"
#include "DetailWidgetRow.h"
#include "DesktopPlatformModule.h"
#include "UEVersion.h"

#define LOCTEXT_NAMESPACE "DirectoryPathCustomization"

FDirectoryPathCustomization::FDirectoryPathCustomization(const FString& InAbsoluteDirectory):
	IPropertyTypeCustomization(),
	AbsoluteDirectory(InAbsoluteDirectory)
{
}

void FDirectoryPathCustomization::CustomizeHeader(const TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                  class FDetailWidgetRow& HeaderRow,
                                                  IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	if (const auto PathProperty = StructPropertyHandle->GetChildHandle("Path"))
	{
		const auto bUseRelativePath = StructPropertyHandle->HasMetaData(TEXT("RelativePath"));

		const TSharedPtr<SWidget> PickerWidget = SAssignNew(BrowseButton, SButton)
#if UE_APP_STYLE_GET
			.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
#else
			.ButtonStyle(FEditorStyle::Get(), "HoverHintOnly")
#endif
			.ToolTipText(LOCTEXT("FolderButtonToolTipText", "Choose a directory from this computer"))
			.OnClicked(FOnClicked::CreateSP(this, &FDirectoryPathCustomization::OnPickDirectory,
			                                PathProperty.ToSharedRef(), bUseRelativePath))
			.ContentPadding(2.0f)
			.ForegroundColor(FSlateColor::UseForeground())
			.IsFocusable(false)
			[
				SNew(SImage)
#if UE_APP_STYLE_GET_BRUSH
				.Image(FAppStyle::GetBrush("PropertyWindow.Button_Ellipsis"))
#else
				.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Ellipsis"))
#endif
				.ColorAndOpacity(FSlateColor::UseForeground())
			];

		HeaderRow.ValueContent()
		         .MinDesiredWidth(125.0f)
		         .MaxDesiredWidth(600.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					PathProperty->CreatePropertyValueWidget()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
				.VAlign(VAlign_Center)
				[
					PickerWidget.ToSharedRef()
				]
			]
			.NameContent()
			[
				StructPropertyHandle->CreatePropertyNameWidget()
			];
	}
}

void FDirectoryPathCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle,
                                                    class IDetailChildrenBuilder& StructBuilder,
                                                    IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

FReply FDirectoryPathCustomization::OnPickDirectory(const TSharedRef<IPropertyHandle> PropertyHandle,
                                                    const bool bUseRelativePath) const
{
	if (const auto DesktopPlatform = FDesktopPlatformModule::Get())
	{
		const auto& ParentWindow = FSlateApplication::Get().FindWidgetWindow(BrowseButton.ToSharedRef());

		const void* ParentWindowHandle = ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()
			                                 ? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
			                                 : nullptr;

		auto StartDirectory = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);

		if (bUseRelativePath && !IsValidPath(StartDirectory, bUseRelativePath))
		{
			StartDirectory = AbsoluteDirectory;
		}

		for (;;)
		{
			if (FString Directory;
				DesktopPlatform->OpenDirectoryDialog(ParentWindowHandle,
				                                     LOCTEXT("FolderDialogTitle", "Choose a directory").ToString(),
				                                     StartDirectory, Directory))
			{
				FText FailureReason;

				if (IsValidPath(Directory, bUseRelativePath, &FailureReason))
				{
					FEditorDirectories::Get().SetLastDirectory(ELastDirectory::GENERIC_IMPORT, Directory);

					if (bUseRelativePath)
					{
						Directory.RightChopInline(AbsoluteDirectory.Len(), false);
					}

					PropertyHandle->SetValue(Directory);
				}
				else
				{
					StartDirectory = Directory;

					FMessageDialog::Open(EAppMsgType::Ok, FailureReason);

					continue;
				}
			}

			break;
		}
	}

	return FReply::Handled();
}

bool FDirectoryPathCustomization::IsValidPath(const FString& AbsolutePath, const bool bUseRelativePath,
                                              FText* const OutReason) const
{
	if (bUseRelativePath)
	{
		if (!AbsolutePath.StartsWith(AbsoluteDirectory))
		{
			if (OutReason)
			{
				*OutReason = FText::Format(LOCTEXT(
					"Error_InvalidRootPath", "The chosen directory must be within {0}"),
				                           FText::FromString(AbsoluteDirectory));
			}

			return false;
		}
	}

	return true;
}

#undef LOCTEXT_NAMESPACE
