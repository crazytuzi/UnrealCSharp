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

	void DoWork();

	void ImmediatelyDoWork();

	void Compile(const TFunction<void()>& InFunction);

private:
	void Compile();

private:
	void OnBeginGenerator();

	void OnEndGenerator();

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

	TSharedPtr<SNotificationItem> NotificationItem;
};
