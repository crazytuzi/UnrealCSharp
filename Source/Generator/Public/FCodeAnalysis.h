#pragma once

class FCodeAnalysis
{
public:
	static GENERATOR_API void CodeAnalysis();

private:
	static void Compile();

	static void Analysis();

	static FString GetProgram();
};
