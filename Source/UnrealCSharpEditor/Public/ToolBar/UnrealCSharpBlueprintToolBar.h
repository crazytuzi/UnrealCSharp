#pragma once

#include "CoreMinimal.h"

class FUnrealCSharpBlueprintToolBar final
{
public:
	FUnrealCSharpBlueprintToolBar();

public:
	void Initialize();

	void Deinitialize();

private:
	void OnEndGenerator();

private:
	void BuildAction();

	TSharedRef<FExtender> GenerateBlueprintExtender(UBlueprint* InBlueprint);

private:
	void SetCodeAnalysisOverrideFilesMap();

	bool HasOverrideFile() const;

	FString GetOverrideFile() const;

	FString GetFileName() const;

private:
	FDelegateHandle OnEndGeneratorDelegateHandle;

	TSharedRef<FUICommandList> CommandList;

	TWeakObjectPtr<UBlueprint> Blueprint;

	TMap<FString, FString> CodeAnalysisOverrideFilesMap;

	TMap<FString, FString> DynamicOverrideFilesMap;
};
