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
	void Compile() const;

	void ImmediatelyCompile() const;

	void Compile(const TArray<FFileChangeData>& InFileChangeData) const;

	void Compile(const TFunction<void()>& InFunction) const;

	bool IsCompiling() const;

private:
	class FCSharpCompilerRunnable* Runnable;

	FRunnableThread* Thread;
};
