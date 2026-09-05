#pragma once

#include "IDirectoryWatcher.h"

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

	void GetCompileProgress(FString& OutMessage, float& OutFraction) const;

	void DoWork();

	void ImmediatelyDoWork(bool bForceCompileInterop = false);

	void Compile(const TFunction<void()>& InFunction, bool bCompileInterop = false, bool bForceCompileInterop = false);

private:
	static FString GetBuildConfiguration();

	void CompileInterop(bool bForceCompileInterop);

	void Compile();

private:
	void OnBeginGenerator();

	void OnEndGenerator();

private:
	void ResetCompileProgress(const FString& InMessage);

	void ParseCompileOutput(const FString& InOutput);

private:
	FDelegateHandle OnBeginGeneratorDelegateHandle;

	FDelegateHandle OnEndGeneratorDelegateHandle;

	TQueue<bool> Tasks;

	TArray<FFileChangeData> FileChanges;

	FCriticalSection CriticalSection;

	FEvent* Event;

	bool bIsCompiling;

	bool bIsGenerating;

	bool bIsStopped;

	mutable FCriticalSection ProgressCriticalSection;

	FString ProgressMessage;

	FString ProgressOutputBuffer;

	int32 CompletedProjectCount;

	int32 TotalProjectCount;

	TSharedPtr<SNotificationItem> NotificationItem;
};
