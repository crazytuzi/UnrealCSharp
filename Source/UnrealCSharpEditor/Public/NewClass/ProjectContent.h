#pragma once

#include "CoreMinimal.h"

struct FProjectContent
{
	FProjectContent(const FString& InName, const FString& InSourcePath):
		Name(InName),
		SourcePath(InSourcePath)
	{
	}

	FProjectContent(FString&& InName, FString&& InSourcePath):
		Name(MoveTemp(InName)),
		SourcePath(MoveTemp(InSourcePath))
	{
	}

	FString Name;

	FString SourcePath;
};
