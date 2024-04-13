#pragma once

#include "IDirectoryWatcher.h"

class FEditorListener
{
public:
	FEditorListener();

	~FEditorListener();

private:
	void OnPostEngineInit();

	void OnPreBeginPIE(const bool);

	void OnPrePIEEnded(const bool);

	void OnCancelPIEEnded();

	void OnBeginGenerator();

	void OnEndGenerator();

	void OnFilesLoaded();

	void OnAssetAdded(const FAssetData& InAssetData) const;

	void OnAssetRemoved(const FAssetData& InAssetData) const;

	void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const;

	void OnAssetUpdated(const FAssetData& InAssetData) const;

	void OnMainFrameCreationFinished(TSharedPtr<SWindow> InRootWindow, bool);

	void OnWindowActivatedEvent();

	void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges);

private:
	void OnAssetChanged(const TFunction<void()>& InGenerator) const;

private:
	FDelegateHandle OnPostEngineInitDelegateHandle;

	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPrePIEEndedDelegateHandle;

	FDelegateHandle OnCancelPIEDelegateHandle;

	FDelegateHandle OnBeginGeneratorDelegateHandle;

	FDelegateHandle OnEndGeneratorDelegateHandle;

	FDelegateHandle OnMainFrameCreationFinishedDelegateHandle;

	FDelegateHandle OnDirectoryChangedDelegateHandle;

private:
	TArray<FFileChangeData> FileChanges;

	bool bIsPIEPlaying;

	bool bIsGenerating;
};
