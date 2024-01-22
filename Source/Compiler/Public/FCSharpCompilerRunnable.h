#pragma once

#include "IDirectoryWatcher.h"

class FCSharpCompilerRunnable final : public FRunnable
{
public:
	FCSharpCompilerRunnable();

public:
	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;

	virtual void Exit() override;

public:
	void EnqueueTask();

	void EnqueueTask(const TArray<FFileChangeData>& FileChangeData);

	bool IsCompiling() const;

	void DoWork();

	void ImmediatelyDoWork();

	void Compile(const TFunction<void()>& InFunction);

private:
	static void Compile();

private:
	TQueue<bool> Tasks;

	TArray<FFileChangeData> FileChanges;

	FCriticalSection CriticalSection;

	FEvent* Event;

	bool bIsCompiling;
};
