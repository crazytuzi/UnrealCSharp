#pragma once

#include "IDirectoryWatcher.h"

class SWindow;

class FEditorListener
{
public:
	FEditorListener();

	~FEditorListener();

private:
	void OnPostEngineInit();

	void OnPreBeginPIE(const bool bIsSimulating);

	void OnPrePIEEnded(const bool bIsSimulating);

	void OnEndPIE(const bool bIsSimulating);

	void OnCancelPIE();

	void OnBeginGenerator();

	void OnEndGenerator();

	void OnCompile(const TArray<FFileChangeData>& InFileChangeData);

	void OnFilesLoaded();

	void OnAssetAdded(const FAssetData& InAssetData) const;

	void OnAssetRemoved(const FAssetData& InAssetData) const;

	void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath) const;

	void OnAssetUpdatedOnDisk(const FAssetData& InAssetData) const;

	void OnMainFrameCreationFinished(TSharedPtr<SWindow>, bool);

	void OnApplicationActivationStateChanged(const bool bIsActive);

	void OnDirectoryChanged(const TArray<FFileChangeData>& InFileChanges);

	void OnBlueprintCompiled();

private:
	void OnAssetChanged(const FAssetData& InAssetData, const TFunction<void()>& InGenerator) const;

	void CompileDirtyBlueprints();

	bool IsCompileRequired() const;

	void RequestCompile();

	void Compile();

	static void TickProgressWindow(const TSharedPtr<SWindow>& InWindow);

	static void WaitForCompile();

private:
	FDelegateHandle OnPostEngineInitDelegateHandle;

	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPrePIEEndedDelegateHandle;

	FDelegateHandle OnEndPIEDelegateHandle;

	FDelegateHandle OnCancelPIEDelegateHandle;

	FDelegateHandle OnBeginGeneratorDelegateHandle;

	FDelegateHandle OnEndGeneratorDelegateHandle;

	FDelegateHandle OnCompileDelegateHandle;

	FDelegateHandle OnMainFrameCreationFinishedDelegateHandle;

	FDelegateHandle OnApplicationActivationStateChangedDelegateHandle;

	FDelegateHandle OnDirectoryChangedDelegateHandle;

	FDelegateHandle OnBlueprintCompiledDelegateHandle;

private:
	TArray<FFileChangeData> FileChanges;

	TMap<FSoftObjectPath, uint32> CrcCompiledSignatures;

	bool bIsPIEPlaying;

	bool bIsPreparingPIE;

	bool bIsGenerating;
};
