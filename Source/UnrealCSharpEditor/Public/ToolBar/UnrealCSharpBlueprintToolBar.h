#pragma once

#include "CoreMinimal.h"

class FUnrealCSharpBlueprintToolBar final
{
public:
	void Initialize();

	void Deinitialize();

private:
	void OnEndGenerator();

private:
	void BuildAction(const TSharedRef<FUICommandList> InCommandList, const TWeakObjectPtr<UBlueprint> InBlueprint);

	TSharedRef<FExtender> GenerateBlueprintExtender(const TSharedRef<FUICommandList> InCommandList,
	                                                const TArray<UObject*> InContextSensitiveObjects);

private:
	void SetCodeAnalysisOverrideFilesMap();

	bool HasOverrideFile(const TWeakObjectPtr<UBlueprint>& InBlueprint) const;

	FString GetOverrideFile(const TWeakObjectPtr<UBlueprint>& InBlueprint) const;

	FString GetFileName(const TWeakObjectPtr<UBlueprint>& InBlueprint) const;

private:
	FDelegateHandle OnEndGeneratorDelegateHandle;

	TMap<FString, FString> CodeAnalysisOverrideFilesMap;

	TMap<FString, FString> DynamicOverrideFilesMap;
};
