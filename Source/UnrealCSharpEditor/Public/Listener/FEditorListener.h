#pragma once

#include "IDirectoryWatcher.h"

class FEditorListener
{
public:
	FEditorListener();

	~FEditorListener();

private:
	static void OnPostEngineInit();

	static void OnPreBeginPIE(const bool);

	static void OnPrePIEEnded(const bool);

	static void OnCancelPIEEnded();

	void OnFilesLoaded();

	void OnAssetAdded(const FAssetData& InAssetData) const;

	void OnAssetRemoved(const FAssetData& InAssetData) const;

	void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const;

	void OnAssetUpdated(const FAssetData& InAssetData) const;

	void OnMainFrameCreationFinished(TSharedPtr<SWindow> InRootWindow, bool);

	void OnWindowActivatedEvent();

	void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges);

private:
	static void OnAssetChanged(const TFunction<void()>& InGenerator);

private:
	FDelegateHandle OnPostEngineInitDelegateHandle;

	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPrePIEEndedDelegateHandle;

	FDelegateHandle OnCancelPIEDelegateHandle;

	FDelegateHandle OnMainFrameCreationFinishedDelegateHandle;

	FDelegateHandle OnDirectoryChangedDelegateHandle;

private:
	TArray<FFileChangeData> FileChanges;

	static bool bIsPIEPlaying;
};
