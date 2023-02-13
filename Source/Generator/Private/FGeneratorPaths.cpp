#include "FGeneratorPaths.h"

#include "Misc/FileHelper.h"

FString FGeneratorPaths::GetManagedBaseName()
{
	return TEXT("Script");
}

FString FGeneratorPaths::GetManagedBasePath()
{
	return FPaths::Combine(FPaths::ProjectDir(), GetManagedBaseName());
}

FString FGeneratorPaths::GetUEManagedProjectName()
{
	return TEXT("UE-Managed");
}

FString FGeneratorPaths::GetUEManagedPath()
{
	return FPaths::Combine(GetManagedBasePath(), GetUEManagedProjectName());
}

FString FGeneratorPaths::GetUEManagedProxyPath()
{
	return FPaths::Combine(GetUEManagedPath(), TEXT("Proxy"));
}

FString FGeneratorPaths::GetGameManagedProjectName()
{
	return TEXT("Game-Managed");
}

FString FGeneratorPaths::GetGameManagedPath()
{
	return FPaths::Combine(GetManagedBasePath(), GetGameManagedProjectName());
}

FString FGeneratorPaths::GetGameManagedProxyPath()
{
	return FPaths::Combine(GetGameManagedPath(), TEXT("Proxy"));
}

static TArray<FString> GameModuleList;

FString FGeneratorPaths::GetGenerationPath(const FString& InternalScriptPath)
{
	check(!InternalScriptPath.IsEmpty() && InternalScriptPath[0] == TEXT('/'));
	
	TArray<FString> Splits;
	
	InternalScriptPath.ParseIntoArray(Splits, TEXT("/"));
	
	if( GameModuleList.Contains(Splits[0])  ||  (Splits[0] == TEXT("Script") && GameModuleList.Contains(Splits[1])) )
	{
		return GetGameManagedProxyPath();
	}
	else
	{
		return GetUEManagedProxyPath();
	}
}

void FGeneratorPaths::BeginCache()
{
	// Scan
	auto TxtFile = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("UnrealCSharp"), TEXT("Intermediate"), TEXT("GameModules.txt"));

	FFileHelper::LoadFileToStringArray(GameModuleList, *TxtFile);

	// Append Game
	GameModuleList.AddUnique(TEXT("Game"));
}

void FGeneratorPaths::EndCache()
{
	GameModuleList.Reset();
}
