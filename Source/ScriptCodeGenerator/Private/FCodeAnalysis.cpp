#include "FCodeAnalysis.h"
#include "Async/Async.h"
#include "Misc/CoreMisc.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Paths.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

void FCodeAnalysis::CodeAnalysis()
{
	RunCompile(MakeCompileCommand());

	RunAnalysis(MakeAnalysisCommand(TArray<FString>()));
}

TFunction<void()> FCodeAnalysis::MakeCodeAnalysisTask(const TArray<FString>& InFiles, TFunction<void()> InOnComplete)
{
	const auto CompileCommand = MakeCompileCommand();

	const auto AnalysisCommand = MakeAnalysisCommand(InFiles);

	return [CompileCommand, AnalysisCommand, InOnComplete]()
	{
		RunCompile(CompileCommand);

		RunAnalysis(AnalysisCommand);

		if (InOnComplete)
		{
			AsyncTask(ENamedThreads::GameThread, [InOnComplete]()
			{
				InOnComplete();
			});
		}
	};
}

FCodeAnalysis::FCommand FCodeAnalysis::MakeCompileCommand()
{
	FCommand Command;

	if (IsProgramOutdated())
	{
		Command.Program = FUnrealCSharpFunctionLibrary::GetDotNet();

		Command.Param = FString::Printf(TEXT(
			"build \"%s\" --nologo -c Debug"
		),
		                                *FUnrealCSharpFunctionLibrary::GetCodeAnalysisProjectPath());
	}

	return Command;
}

FCodeAnalysis::FCommand FCodeAnalysis::MakeAnalysisCommand(const TArray<FString>& InFiles)
{
	FCommand Command;

	Command.Program = GetProgramPath();

	Command.Param = GetAnalysisParam(InFiles);

	return Command;
}

void FCodeAnalysis::RunCompile(const FCommand& InCommand)
{
	if (!InCommand.Program.IsEmpty())
	{
		RunCommand(InCommand, 600.0, 120.0);
	}
}

void FCodeAnalysis::RunAnalysis(const FCommand& InCommand)
{
	RunCommand(InCommand, AnalysisTimeoutSeconds, AnalysisSilenceTimeoutSeconds);
}

void FCodeAnalysis::RunCommand(const FCommand& InCommand, const double InTimeoutSeconds,
                               const double InSilenceTimeoutSeconds)
{
	FUnrealCSharpFunctionLibrary::SyncProcess(InCommand.Program, InCommand.Param, [](const int32, const FString&)
	                                          {
	                                          }, FString(), {}, []()
	                                          {
		                                          return IsEngineExitRequested();
	                                          }, InTimeoutSeconds, InSilenceTimeoutSeconds);
}

FString FCodeAnalysis::GetProgramPath()
{
	return FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(),
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
}

FString FCodeAnalysis::GetAnalysisParam(const TArray<FString>& InFiles)
{
	auto AnalysisParam = FString::Printf(TEXT(
		"%s \"%s\""
	),
	                                     InFiles.IsEmpty() ? TEXT("false") : TEXT("true"),
	                                     *FPaths::ConvertRelativePathToFull(
		                                     FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()));

	if (InFiles.IsEmpty())
	{
		AnalysisParam += FString::Printf(TEXT(
			" \"%s\""
		),
		                                 *FPaths::ConvertRelativePathToFull(
			                                 FUnrealCSharpFunctionLibrary::GetGameDirectory()));

		for (const auto& CustomProjectsDirectory : FUnrealCSharpFunctionLibrary::GetCustomProjectsDirectory())
		{
			AnalysisParam += FString::Printf(TEXT(
				" \"%s\""
			),
			                                 *CustomProjectsDirectory);
		}
	}
	else
	{
		for (const auto& File : InFiles)
		{
			AnalysisParam += FString::Printf(TEXT(
				" \"%s\""
			),
			                                 *File);
		}
	}

	return AnalysisParam;
}

bool FCodeAnalysis::IsProgramOutdated()
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	auto Timestamp = FDateTime::MinValue();

	const auto SharedProps = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetFullScriptDirectory(),
	                                         SHARED_NAME + PROPS_SUFFIX);

	if (PlatformFile.FileExists(*SharedProps))
	{
		Timestamp = PlatformFile.GetTimeStamp(*SharedProps);
	}

	PlatformFile.IterateDirectory(
		*FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(),
		[&](const TCHAR* InFilenameOrDirectory, const bool bIsDirectory) -> bool
		{
			if (const auto Extension = FPaths::GetExtension(InFilenameOrDirectory);
				!bIsDirectory && (Extension == CSHARP_SUFFIX.RightChop(1) || Extension == PROJECT_SUFFIX.RightChop(1)))
			{
				Timestamp = FMath::Max(Timestamp, PlatformFile.GetTimeStamp(InFilenameOrDirectory));
			}

			return true;
		});

	const TArray<FString> Paths{
		GetProgramPath(),
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(), CODE_ANALYSIS_NAME + DLL_SUFFIX)
	};

	for (const auto& Path : Paths)
	{
		if (!PlatformFile.FileExists(*Path) || PlatformFile.GetTimeStamp(*Path) < Timestamp)
		{
			return true;
		}
	}

	return false;
}
