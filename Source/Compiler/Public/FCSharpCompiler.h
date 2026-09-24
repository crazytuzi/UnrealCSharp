#pragma once

#include "IDirectoryWatcher.h"

class COMPILER_API FCSharpCompiler
{
public:
	FCSharpCompiler();

	~FCSharpCompiler();

public:
	static FCSharpCompiler& Get();

public:
	void AsyncCompile() const;

	void AsyncCompile(const TArray<FFileChangeData>& InFileChangeData) const;

	bool SyncCompile() const;

	void Compile(const TFunction<void()>& InFunction) const;

	void ImmediatelyCompile(bool bForceCompileInterop = false) const;

	bool IsCompiling() const;

	FString GetCompileProgress() const;

public:
	static constexpr int32 PollsPerSecond = 120;

	static constexpr float PollIntervalSeconds = 1.0f / PollsPerSecond;

private:
	class FCSharpCompilerRunnable* Runnable;

	FRunnableThread* Thread;
};
