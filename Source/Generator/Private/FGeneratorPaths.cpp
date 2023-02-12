#include "FGeneratorPaths.h"

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

FString FGeneratorPaths::GetGenerationPath(const FString& InternalScriptPath)
{
	check(InternalScriptPath[0] == TEXT('/'));
	if(InternalScriptPath.StartsWith(TEXT("/Game/")))
	{
		return GetGameManagedPath();
	}
	else
	{
		return GetUEManagedProxyPath();
	}
}
