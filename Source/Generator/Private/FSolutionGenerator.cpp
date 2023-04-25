#include "FSolutionGenerator.h"
#include "Macro.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Misc/FileHelper.h"

void FSolutionGenerator::Generator()
{
	Compile();

	const auto PluginPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() / PLUGIN_NAME);

	const auto TemplatePath = PluginPath / TEMPLATE;

	CopyCSProj(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetUEPath(),
		                FUnrealCSharpFunctionLibrary::GetUEProjectName() + PROJECT_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetUEProjectName() + PROJECT_SUFFIX);

	CopyCSProj(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGamePath(),
		                FUnrealCSharpFunctionLibrary::GetGameProjectName() + PROJECT_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetGameProjectName() + PROJECT_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetBasePath(),
		                FUnrealCSharpFunctionLibrary::GetBaseName() + SOLUTION_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetBaseName() + SOLUTION_SUFFIX);
}

void FSolutionGenerator::Compile()
{
	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CodeAnalysisPath = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectPluginsDir() / PLUGIN_NAME, SCRIPT, ASSEMBLY_UTIL));

	const auto CompileParam = FString::Printf(TEXT(
		"build %s/%s.csproj --nologo -c Debug"
	),
	                                          *CodeAnalysisPath,
	                                          *ASSEMBLY_UTIL
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

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src)
{
	auto& FileManager = IFileManager::Get();

	if (!FileManager.FileExists(*Dest))
	{
		FileManager.Copy(*Dest, *Src);
	}
}

void FSolutionGenerator::CopyCSProj(const FString& Dest, const FString& Src)
{
	FString Result;

	FFileHelper::LoadFileToString(Result, *Src);

	FString DefineConstants;

	for (auto MajorVersion = 4; MajorVersion <= ENGINE_MAJOR_VERSION; ++MajorVersion)
	{
		if (MajorVersion == ENGINE_MAJOR_VERSION)
		{
			for (auto MinorVersion = 0; MinorVersion <= ENGINE_MINOR_VERSION; ++MinorVersion)
			{
				DefineConstants += FString::Printf(TEXT(
					"UE_%d_%d_OR_LATER;"
				),
				                                   MajorVersion,
				                                   MinorVersion
				);
			}
		}
		else
		{
			for (auto MinorVersion = 0; MinorVersion <= 30; ++MinorVersion)
			{
				DefineConstants += FString::Printf(TEXT(
					"UE_%d_%d_OR_LATER;"
				),
				                                   MajorVersion,
				                                   MinorVersion
				);
			}
		}
	}

	DefineConstants = FString::Printf(TEXT(
		"<DefineConstants>$(DefineConstants);%s</DefineConstants>"
	),
	                                  *DefineConstants
	);

	Result = Result.Replace(TEXT("<DefineConstants>$(DefineConstants);</DefineConstants>"), *DefineConstants);

	auto& FileManager = IFileManager::Get();

	FFileHelper::SaveStringToFile(Result, *Dest, FFileHelper::EEncodingOptions::ForceUTF8, &FileManager);
}
