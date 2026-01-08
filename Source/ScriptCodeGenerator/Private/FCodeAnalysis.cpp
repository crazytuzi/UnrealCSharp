#include "FCodeAnalysis.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

void FCodeAnalysis::CodeAnalysis()
{
	Compile();

	Analysis();
}

void FCodeAnalysis::Analysis(const FString& InFile)
{
	const auto Program = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(),
	                                     FString::Printf(TEXT(
		                                     "%s%s"
	                                     ),
	                                                     *CODE_ANALYSIS_NAME,
#if PLATFORM_WINDOWS
	                                                     TEXT(".exe")
#else
	                                                     TEXT("")
#endif
	                                     ));

	const auto AnalysisParam = FString::Printf(TEXT(
		"true \"%s\" \"%s\""
	),
	                                           *FPaths::ConvertRelativePathToFull(
		                                           FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()),
	                                           *InFile
	);

	FUnrealCSharpFunctionLibrary::SyncProcess(Program, AnalysisParam, [](const int32, const FString&)
	{
	});
}

void FCodeAnalysis::Compile()
{
	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CompileParam = FString::Printf(TEXT(
		"build \"%s\" --nologo -c Debug"
	),
	                                          *FUnrealCSharpFunctionLibrary::GetCodeAnalysisProjectPath()
	);

	FUnrealCSharpFunctionLibrary::SyncProcess(CompileTool, CompileParam, [](const int32, const FString&)
	{
	});
}

void FCodeAnalysis::Analysis()
{
	const auto Program = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(),
	                                     FString::Printf(TEXT(
		                                     "%s%s"
	                                     ),
	                                                     *CODE_ANALYSIS_NAME,
#if PLATFORM_WINDOWS
	                                                     TEXT(".exe")
#else
	                                                     TEXT("")
#endif
	                                     ));

	auto AnalysisParam = FString::Printf(TEXT(
		"false \"%s\" \"%s\""
	),
	                                     *FPaths::ConvertRelativePathToFull(
		                                     FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()),
	                                     *FPaths::ConvertRelativePathToFull(
		                                     FUnrealCSharpFunctionLibrary::GetGameDirectory())
	);

	for (const auto& CustomProjectsDirectory : FUnrealCSharpFunctionLibrary::GetCustomProjectsDirectory())
	{
		AnalysisParam += FString::Printf(TEXT(
			" \"%s\""
		),
		                                 *CustomProjectsDirectory
		);
	}

	FUnrealCSharpFunctionLibrary::SyncProcess(Program, AnalysisParam, [](const int32, const FString&)
	{
	});
}
