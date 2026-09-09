#pragma once

#include "IDirectoryWatcher.h"
#include "Containers/Ticker.h"
#include "FCSharpCompileProgress.h"

class FCSharpCompilerRunnable final : public FRunnable
{
public:
	FCSharpCompilerRunnable();

	virtual ~FCSharpCompilerRunnable() override;

public:
	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;

	virtual void Exit() override;

public:
	void EnqueueTask();

	void EnqueueTask(const TArray<FFileChangeData>& InFileChangeData);

	bool IsCompiling() const;

	FString GetCompileProgress() const;

	void DoWork();

	void ImmediatelyDoWork(bool bForceCompileInterop = false);

	void Compile(const TFunction<void(const TArray<FFileChangeData>&)>& InFunction, bool bCompileInterop = false,
	             bool bForceCompileInterop = false, bool bReloadImmediately = false);

private:
	static FString GetBuildConfiguration();

	bool CompileInterop(bool bForceCompileInterop);

	bool Compile();

	void ShowCompileResultNotification(bool bSucceeded) const;

private:
	void OnBeginGenerator();

	void OnEndGenerator();

private:
	FDelegateHandle OnBeginGeneratorDelegateHandle;

	FDelegateHandle OnEndGeneratorDelegateHandle;

	FTSTicker::FDelegateHandle ProgressTickerHandle;

	TQueue<bool> Tasks;

	TArray<FFileChangeData> FileChanges;

	FCriticalSection CriticalSection;

	FEvent* Event;

	std::atomic<bool> bIsCompiling;

	bool bIsGenerating;

	bool bIsStopped;

	FCSharpCompileProgress CompileProgress;

	TSharedPtr<SNotificationItem> NotificationItem;
};
