#include "FCodeAnalysis.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Paths.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

void FCodeAnalysis::CodeAnalysis()
{
	Compile();

	Analysis();
}

void FCodeAnalysis::Analysis(const FString& InFile)
{
	const auto AnalysisParam = FString::Printf(TEXT(
		"true \"%s\" \"%s\""
	),
	                                           *FPaths::ConvertRelativePathToFull(
		                                           FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()),
	                                           *InFile
	);

	FUnrealCSharpFunctionLibrary::SyncProcess(GetProgramPath(), AnalysisParam, [](const int32, const FString&)
	{
	});
}

void FCodeAnalysis::Compile()
{
	if (IsProgramOutdated())
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
}

void FCodeAnalysis::Analysis()
{
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

	FUnrealCSharpFunctionLibrary::SyncProcess(GetProgramPath(), AnalysisParam, [](const int32, const FString&)
	{
	});
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
