#include "FCodeAnalysis.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Macro.h"

void FCodeAnalysis::CodeAnalysis()
{
	const auto Program = GetProgram();

	auto& FileManager = IFileManager::Get();

	if (!FileManager.FileExists(*Program))
	{
		Compile();
	}

	Analysis();
}

void FCodeAnalysis::Compile()
{
	const auto CodeAnalysisPath = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectPluginsDir() / PLUGIN_NAME, SCRIPT, CODE_ANALYSIS));

	const auto CompileTool = FUnrealCSharpFunctionLibrary::GetCompileTool();

	const auto CompileParam = FPaths::ConvertRelativePathToFull(FString::Printf(TEXT(
		"%s\\%s.csproj /build \"Debug\""
	),
		*CodeAnalysisPath,
		*CODE_ANALYSIS
	));

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

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

void FCodeAnalysis::Analysis()
{
	const auto Program = GetProgram();

	const auto CompileParam = FString::Printf(TEXT(
		"%s %s"
	),
	                                          *FUnrealCSharpFunctionLibrary::GetGamePath(),
	                                          *FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath()
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

FString FCodeAnalysis::GetProgram()
{
	return FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectPluginsDir() / PLUGIN_NAME, SCRIPT, CODE_ANALYSIS,
		                TEXT("bin"),
		                TEXT("Debug"),
		                TEXT("net7.0"),
		                FString::Printf(TEXT(
			                "%s.exe"
		                ),
		                                *CODE_ANALYSIS
		                )));
}
