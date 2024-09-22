#pragma once

#include "CoreMinimal.h"

class FDoxygenConverter
{
public:
	explicit FDoxygenConverter(const FString& InIndent = TEXT(""));

	FString operator()(const FStringView& InText) const;

private:
	FString Indent;
};
