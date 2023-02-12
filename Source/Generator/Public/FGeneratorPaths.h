#pragma once

#include "CoreMinimal.h"

class FGeneratorPaths
{
public:
	static FString GetManagedBaseName();
	
	static FString GetManagedBasePath();

	static FString GetUEManagedProjectName();
	
	static FString GetUEManagedPath();
	
	static FString GetUEManagedProxyPath();

	static FString GetGameManagedProjectName();

	static FString GetGameManagedPath();

	static FString GetGameManagedProxyPath();
	
	static FString GetGenerationPath(const FString& InternalScriptPath);
};