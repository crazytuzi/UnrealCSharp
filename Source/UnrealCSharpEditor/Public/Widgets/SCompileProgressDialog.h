#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class STextBlock;

class SCompileProgressDialog final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCompileProgressDialog)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments&);

	void UpdateProgress(const FString& InStatusMessage, int32 InElapsedSeconds) const;

private:
	TSharedPtr<STextBlock> StatusText;

	TSharedPtr<STextBlock> ElapsedText;
};
