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

	void OnFilesLoaded();

	void OnAssetAdded(const FAssetData& InAssetData) const;

	void OnAssetRemoved(const FAssetData& InAssetData) const;

	void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const;

	void OnAssetUpdated(const FAssetData& InAssetData) const;

	void OnMainFrameCreationFinished(TSharedPtr<SWindow> InRootWindow, bool);

	void OnWindowActivatedEvent();

	void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges);

private:
	void OnAssetChanged(const FAssetData& InAssetData,
	                    const TFunction<void(const UClass*)> InBlueprint,
	                    const TFunction<void(const class UUserDefinedStruct*)> InUserDefinedStruct,
	                    const TFunction<void(const class UUserDefinedEnum*)> InUserDefinedEnum) const;

private:
	FDelegateHandle OnPostEngineInitDelegateHandle;

	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnMainFrameCreationFinishedDelegateHandle;

	FDelegateHandle OnDirectoryChangedDelegateHandle;

private:
	TArray<FFileChangeData> FileChanges;
};
