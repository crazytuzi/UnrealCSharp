#include "FCodeAnalysis.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

void FCodeAnalysis::CodeAnalysis()
{
	Compile();

	Analysis();
}

void FCodeAnalysis::Compile()
{
	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CodeAnalysisPath = FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath();

	const auto CompileParam = FString::Printf(TEXT(
		"build \"%s/%s.csproj\" --nologo -c Debug"
	),
	                                          *CodeAnalysisPath,
	                                          *CODE_ANALYSIS
	);

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FString Result;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	auto ProcessHandle = FPlatformProcess::CreateProc(
		*CompileTool,
		*CompileParam,
		false,
		true,
		true,
		&OutProcessID,
		1,
		nullptr,
		WritePipe,
		ReadPipe);

	while (ProcessHandle.IsValid() && FPlatformProcess::IsApplicationRunning(OutProcessID))
	{
		FPlatformProcess::Sleep(0.01f);

		Result.Append(FPlatformProcess::ReadPipe(ReadPipe));
	}

	auto ReturnCode = 0;

	if (FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode))
	{
		if (ReturnCode == 0)
		{
			// @TODO
		}
		else
		{
			// @TODO
		}
	}

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);

	FPlatformProcess::CloseProc(ProcessHandle);
}

void FCodeAnalysis::Analysis()
{
	const auto Program = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetCodeAnalysisCSProjPath(),
	                                     FString::Printf(TEXT(
		                                     "%s%s"
	                                     ),
	                                                     *CODE_ANALYSIS,
#if PLATFORM_WINDOWS
	                                                     TEXT(".exe")
#else
	                                                     TEXT("")
#endif
	                                     ));

	const auto CompileParam = FString::Printf(TEXT(
		"\"%s\" \"%s\""
	),
	                                          *FPaths::ConvertRelativePathToFull(
		                                          FUnrealCSharpFunctionLibrary::GetGamePath()),
	                                          *FPaths::ConvertRelativePathToFull(
		                                          FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath())
	);

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	auto ProcessHandle = FPlatformProcess::CreateProc(
		*Program,
		*CompileParam,
		false,
		true,
		true,
		&OutProcessID,
		1,
		nullptr,
		WritePipe,
		ReadPipe);

	while (ProcessHandle.IsValid() && FPlatformProcess::IsApplicationRunning(OutProcessID))
	{
		FPlatformProcess::Sleep(0.01f);
	}

	auto ReturnCode = 0;

	if (FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode))
	{
		if (ReturnCode == 0)
		{
			// @TODO
		}
		else
		{
			// @TODO
		}
	}
}
