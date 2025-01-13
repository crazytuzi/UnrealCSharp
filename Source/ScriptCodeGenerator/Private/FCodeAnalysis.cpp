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

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	auto ProcessHandle = FPlatformProcess::CreateProc(
		*Program,
		*AnalysisParam,
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

void FCodeAnalysis::Compile()
{
	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CompileParam = FString::Printf(TEXT(
		"build \"%s\" --nologo -c Debug"
	),
	                                          *FUnrealCSharpFunctionLibrary::GetCodeAnalysisProjectPath()
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

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	auto ProcessHandle = FPlatformProcess::CreateProc(
		*Program,
		*AnalysisParam,
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
