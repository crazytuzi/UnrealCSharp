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

	bool SyncCompile();

	void Compile(const TFunction<void(const TArray<FFileChangeData>&)>& InFunction, bool bCompileInterop = false,
	             bool bForceCompileInterop = false, bool bReloadImmediately = false);

private:
	static FString GetBuildConfiguration();

	bool CompileInterop(bool bForceCompileInterop);

	bool Compile();

	bool CompileGame(FString& OutResult, const TFunction<void(const FString&)>& InOnOutput);

	void CompileInternal(const TFunction<void(const TArray<FFileChangeData>&)>& InFunction, bool bCompileInterop,
	                     bool bForceCompileInterop, bool bReloadImmediately);

	void AcquireCompile();

	void ReleaseCompile();

	void ShowCompileResultNotification(bool bSucceeded) const;

private:
	void OnBeginGenerator();

	void OnEndGenerator();

private:
	struct FCSharpCompileNotification
	{
		FCSharpCompileProgress Progress;

		TSharedPtr<SNotificationItem> NotificationItem;

		FTSTicker::FDelegateHandle ProgressTickerHandle;

		std::atomic<bool> bIsCompiling{false};

		std::atomic<bool> bIsAlive{true};
	};

	FDelegateHandle OnBeginGeneratorDelegateHandle;

	FDelegateHandle OnEndGeneratorDelegateHandle;

	TArray<FFileChangeData> FileChanges;

	mutable FCriticalSection CriticalSection;

	FEvent* Event;

	std::atomic<bool> bIsCompiling;

	std::atomic<bool> bIsGenerating;

	std::atomic<bool> bIsStopped;

	std::atomic<bool> bIsPending;

	const TSharedRef<FCSharpCompileNotification> CompileNotification = MakeShared<FCSharpCompileNotification>();
};
