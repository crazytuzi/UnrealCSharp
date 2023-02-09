#pragma once

class COMPILER_API FCSharpCompiler
{
public:
	FCSharpCompiler();

	~FCSharpCompiler();

public:
	static FCSharpCompiler& Get();

public:
	void Compile() const;

	bool IsCompiling() const;

private:
	class FCSharpCompilerRunnable* Runnable;
};
