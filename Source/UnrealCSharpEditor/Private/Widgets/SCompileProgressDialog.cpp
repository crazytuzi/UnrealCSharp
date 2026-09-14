#include "Widgets/SCompileProgressDialog.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateTypes.h"

#define LOCTEXT_NAMESPACE "CompileProgressDialog"

void SCompileProgressDialog::Construct(const FArguments&)
{
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(400.f)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(FMargin(24.f, 16.f, 24.f, 0.f))
			[
				SNew(STextBlock)
				.Font(FCoreStyle::GetDefaultFontStyle(TEXT("Bold"), 12))
				.Text(LOCTEXT("Title", "Compiling Scripts"))
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(FMargin(24.f, 12.f, 24.f, 0.f))
			[
				SNew(SBox)
				.WidthOverride(352.f)
				.HeightOverride(12.f)
				[
					SNew(SProgressBar)
					.Style(&FCoreStyle::Get().GetWidgetStyle<FProgressBarStyle>(TEXT("ProgressBar")))
				]
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(FMargin(24.f, 12.f, 24.f, 0.f))
			[
				SAssignNew(StatusText, STextBlock)
				.Text(LOCTEXT("PreparingStatus", "Preparing"))
				.AutoWrapText(true)
			]

			+ SVerticalBox::Slot().AutoHeight().Padding(FMargin(24.f, 6.f, 24.f, 18.f))
			[
				SAssignNew(ElapsedText, STextBlock)
				.ColorAndOpacity(FSlateColor(FLinearColor(0.55f, 0.55f, 0.55f)))
				.Text(LOCTEXT("PIEHint", "PIE will start automatically"))
				.AutoWrapText(true)
			]
		]
	];
}

void SCompileProgressDialog::UpdateProgress(const FString& InStatusMessage, const int32 InElapsedSeconds) const
{
	if (StatusText.IsValid())
	{
		const auto StatusMessage = InStatusMessage.IsEmpty()
			                           ? LOCTEXT("CompilingStatus", "Compiling")
			                           : FText::FromString(InStatusMessage);

		StatusText->SetText(StatusMessage);
	}

	if (ElapsedText.IsValid())
	{
		const auto ElapsedMessage = FText::Format(
			LOCTEXT("ElapsedTime", "Elapsed: {0}s - PIE will start automatically"),
			FText::AsNumber(InElapsedSeconds));

		ElapsedText->SetText(ElapsedMessage);
	}
}

#undef LOCTEXT_NAMESPACE
