#pragma once

class FCodeAnalysis
{
public:
	static GENERATOR_API void CodeAnalysis();

	static GENERATOR_API void Analysis(const FString& InFile);

private:
	static void Compile();

	static void Analysis();
};
