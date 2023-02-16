#include "FSolutionGenerator.h"
#include "FGeneratorCore.h"
#include "FGeneratorPaths.h"
#include "HAL/IPlatformFileModule.h"

void FSolutionGenerator::Generator()
{
	auto PluginDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() / TEXT("UnrealCSharp"));
	
	auto PluginContentDir = PluginDir / TEXT("Content");

	auto TemplateDir = PluginContentDir / TEXT("Template");

	// UE-Managed.csproj
	
	auto UECsprojFilename = FGeneratorPaths::GetUEManagedProjectName() + TEXT(".csproj");
	
	auto UECsrojFullFilePath = FPaths::Combine(FGeneratorPaths::GetUEManagedPath(), UECsprojFilename);

	auto& FileManager = IFileManager::Get();
	
	if(!FileManager.FileExists(*UECsrojFullFilePath))
	{
		FString TemplatePath = TemplateDir / UECsprojFilename;
		
		FileManager.Copy(*UECsrojFullFilePath, *TemplatePath);
	}

	// Game-Managed.csproj
	
	auto GameCsprojFilename = FGeneratorPaths::GetGameManagedProjectName() + TEXT(".csproj");
	
	auto GameCsprojFullFilePath = FPaths::Combine(FGeneratorPaths::GetGameManagedPath(), GameCsprojFilename);

	if(!FileManager.FileExists(*GameCsprojFullFilePath))
	{
		FString TemplatePath = TemplateDir / GameCsprojFilename;
		
		FileManager.Copy(*GameCsprojFullFilePath, *TemplatePath);
	}

	// Script.sln
	
	auto SlnFilename = FGeneratorPaths::GetManagedBaseName() + TEXT(".sln");
	
	auto SlnFullFilePath = FPaths::Combine(FGeneratorPaths::GetManagedBasePath(), SlnFilename);

	if(!FileManager.FileExists(*SlnFullFilePath))
	{
		FString TemplatePath = TemplateDir / SlnFilename;
		
		FileManager.Copy(*SlnFullFilePath, *TemplatePath);
	}
	
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	PlatformFile.CopyDirectoryTree(*(FGeneratorPaths::GetUEManagedPath()), *(PluginDir / TEXT("Script")), true);
	
}
