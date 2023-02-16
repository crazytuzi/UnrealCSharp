#pragma once

#include "CoreMinimal.h"

class FGeneratorPaths
{
public:
	static UNREALCSHARPCORE_API FString GetManagedBaseName();
	
	static UNREALCSHARPCORE_API FString GetManagedBasePath();

	static UNREALCSHARPCORE_API FString GetUEManagedProjectName();
	
	static UNREALCSHARPCORE_API FString GetUEManagedPath();
	
	static UNREALCSHARPCORE_API FString GetUEManagedProxyPath();

	static UNREALCSHARPCORE_API FString GetGameManagedProjectName();

	static UNREALCSHARPCORE_API FString GetGameManagedPath();

	static UNREALCSHARPCORE_API FString GetGameManagedProxyPath();
	
	static UNREALCSHARPCORE_API FString GetGenerationPath(const FString& InternalScriptPath);
	
};
