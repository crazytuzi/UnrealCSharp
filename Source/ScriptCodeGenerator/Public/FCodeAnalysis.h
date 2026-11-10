#pragma once

class FCodeAnalysis
{
public:
	struct FCommand
	{
		FString Program;

		FString Param;
	};

public:
	static SCRIPTCODEGENERATOR_API void CodeAnalysis();

	static SCRIPTCODEGENERATOR_API TFunction<void()> MakeCodeAnalysisTask(const TArray<FString>& InFiles = {},
	                                                                      TFunction<void()> InOnComplete = {});

private:
	static FCommand MakeCompileCommand();

	static FCommand MakeAnalysisCommand(const TArray<FString>& InFiles);

	static void RunCompile(const FCommand& InCommand);

	static void RunAnalysis(const FCommand& InCommand);

	static void RunCommand(const FCommand& InCommand, double InTimeoutSeconds, double InSilenceTimeoutSeconds);

	static FString GetProgramPath();

	static FString GetAnalysisParam(const TArray<FString>& InFiles);

	static bool IsProgramOutdated();

private:
	static constexpr double AnalysisTimeoutSeconds = 1800.0;

	static constexpr double AnalysisSilenceTimeoutSeconds = 300.0;
};
