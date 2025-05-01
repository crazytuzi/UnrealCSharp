﻿#pragma once

#include "IDirectoryWatcher.h"

class FEditorListener
{
public:
	FEditorListener();

	~FEditorListener();

private:
	void OnPostEngineInit();

	void OnPreBeginPIE(const bool bIsSimulating);

	void OnPrePIEEnded(const bool bIsSimulating);

	void OnCancelPIE();

	void OnBeginGenerator();

	void OnEndGenerator();

	void OnCompile(const TArray<FFileChangeData>& InFileChangeData);

	void OnFilesLoaded();

	void OnAssetAdded(const FAssetData& InAssetData) const;

	void OnAssetRemoved(const FAssetData& InAssetData) const;

	void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const;

	void OnAssetUpdated(const FAssetData& InAssetData) const;

	void OnMainFrameCreationFinished(TSharedPtr<SWindow>, bool);

	void OnApplicationActivationStateChanged(const bool IsActive);

	void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges);

private:
	void OnAssetChanged(const TFunction<void()>& InGenerator) const;

private:
	bool IsAssetModifyRecently(const FAssetData& InAssetData, int32 ThresholdSeconds = 5) const;

private:
	FDelegateHandle OnPostEngineInitDelegateHandle;

	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPrePIEEndedDelegateHandle;

	FDelegateHandle OnCancelPIEDelegateHandle;

	FDelegateHandle OnBeginGeneratorDelegateHandle;

	FDelegateHandle OnEndGeneratorDelegateHandle;

	FDelegateHandle OnCompileDelegateHandle;

	FDelegateHandle OnMainFrameCreationFinishedDelegateHandle;

	FDelegateHandle OnApplicationActivationStateChangedDelegateHandle;

	FDelegateHandle OnDirectoryChangedDelegateHandle;

private:
	TArray<FFileChangeData> FileChanges;

	bool bIsPIEPlaying;

	bool bIsGenerating;
};
