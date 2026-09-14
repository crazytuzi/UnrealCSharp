#include "FCSharpCompileProgress.h"
#include "Misc/Paths.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

const TCHAR* const FCSharpCompileProgress::StagePreparing = TEXT("Preparing compile");

const TCHAR* const FCSharpCompileProgress::StageRestoring = TEXT("Restoring NuGet packages");

const TCHAR* const FCSharpCompileProgress::StageCompilingInterop = TEXT("Compiling Interop");

const TCHAR* const FCSharpCompileProgress::StageCompilingUE = TEXT("Compiling UE");

const TCHAR* const FCSharpCompileProgress::StageCompilingGame = TEXT("Compiling Game");

const TCHAR* const FCSharpCompileProgress::StagePublishing = TEXT("Publishing");

const TCHAR* const FCSharpCompileProgress::StageSucceeded = TEXT("Compile succeeded");

const TCHAR* const FCSharpCompileProgress::StageFailed = TEXT("Compile failed");

void FCSharpCompileProgress::SetStage(const FString& InStage)
{
	FScopeLock ScopeLock(&CriticalSection);

	Stage = InStage;

	if (InStage == StageCompilingInterop)
	{
		CompilePhase = ECompilePhase::Interop;
	}
	else if (InStage == StageCompilingUE || InStage == StageCompilingGame)
	{
		CompilePhase = ECompilePhase::Game;
	}

	PendingOutput.Empty();
}

void FCSharpCompileProgress::SetOutput(const FString& InOutput)
{
	FScopeLock ScopeLock(&CriticalSection);

	PendingOutput.Append(InOutput);

	int32 Index = INDEX_NONE;

	while (PendingOutput.FindChar(TEXT('\n'), Index))
	{
		auto Line = PendingOutput.Left(Index);

		PendingOutput.MidInline(Index + 1);

		ProcessLine(Line);
	}
}

void FCSharpCompileProgress::Flush()
{
	FScopeLock ScopeLock(&CriticalSection);

	ProcessLine(PendingOutput);

	PendingOutput.Empty();
}

FString FCSharpCompileProgress::GetStage() const
{
	FScopeLock ScopeLock(&const_cast<FCSharpCompileProgress*>(this)->CriticalSection);

	return Stage;
}

void FCSharpCompileProgress::ProcessLine(const FString& InLine)
{
	auto Line = InLine;

	Line.TrimStartAndEndInline();

	if (!Line.IsEmpty())
	{
		if (const auto ParsedStage = ParseLine(Line);
			!ParsedStage.IsEmpty())
		{
			Stage = ParsedStage;
		}
	}
}

FString FCSharpCompileProgress::ParseLine(const FString& InLine) const
{
	if (InLine.Contains(TEXT(": error ")) || InLine.Contains(TEXT("Build FAILED")))
	{
		return StageFailed;
	}

	if (InLine.Contains(TEXT("Build succeeded")))
	{
		return StageSucceeded;
	}

	if (InLine.Contains(TEXT("Determining projects to restore")) ||
		InLine.Contains(TEXT("Restored ")))
	{
		return StageRestoring;
	}

	if (InLine.Contains(TEXT("up-to-date for restore")))
	{
		return CompilePhase == ECompilePhase::Interop ? StageCompilingInterop : StageCompilingUE;
	}

	const auto Index = InLine.Find(TEXT(" -> "), ESearchCase::CaseSensitive);

	if (Index == INDEX_NONE)
	{
		return FString();
	}

	const auto Project = FPaths::GetBaseFilename(InLine.Left(Index).TrimStartAndEnd());

	const auto UEName = FUnrealCSharpFunctionLibrary::GetUEName();

	const auto GameName = FUnrealCSharpFunctionLibrary::GetGameName();

	if (Project == UEName)
	{
		return StageCompilingGame;
	}

	if (Project == GameName)
	{
		return StagePublishing;
	}

	return FString();
}
