#pragma once

class FCodeAnalysis
{
public:
	static SCRIPTCODEGENERATOR_API void CodeAnalysis();

	static SCRIPTCODEGENERATOR_API void Analysis(const FString& InFile);

private:
	static void Compile();

	static void Analysis();
};
