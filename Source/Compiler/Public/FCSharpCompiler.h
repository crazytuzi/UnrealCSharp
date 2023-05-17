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

	void Compile(const TArray<FFileChangeData>& FileChangeData) const;

	bool IsCompiling() const;

private:
	class FCSharpCompilerRunnable* Runnable;
};
