#include "FSolutionGenerator.h"
#include "Macro.h"
#include "FUnrealCSharpFunctionLibrary.h"

void FSolutionGenerator::Generator()
{
	const auto PluginPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() / PLUGIN_NAME);

	const auto TemplatePath = PluginPath / TEMPLATE;

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetUEPath(),
		                FUnrealCSharpFunctionLibrary::GetUEProjectName() + PROJECT_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetUEProjectName() + PROJECT_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGamePath(),
		                FUnrealCSharpFunctionLibrary::GetGameProjectName() + PROJECT_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetGameProjectName() + PROJECT_SUFFIX);

	CopyTemplate(
		FPaths::Combine(FUnrealCSharpFunctionLibrary::GetBasePath(),
		                FUnrealCSharpFunctionLibrary::GetBaseName() + SOLUTION_SUFFIX),
		TemplatePath / FUnrealCSharpFunctionLibrary::GetBaseName() + SOLUTION_SUFFIX);

	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	PlatformFile.CopyDirectoryTree(*(FUnrealCSharpFunctionLibrary::GetUEPath()), *(PluginPath / SCRIPT), true);
}

void FSolutionGenerator::CopyTemplate(const FString& Dest, const FString& Src)
{
	auto& FileManager = IFileManager::Get();

	if (!FileManager.FileExists(*Dest))
	{
		FileManager.Copy(*Dest, *Src);
	}
}
