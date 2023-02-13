#pragma once

#include "CoreMinimal.h"

class FGeneratorPaths
{
public:
	static GENERATOR_API FString GetManagedBaseName();
	
	static GENERATOR_API FString GetManagedBasePath();

	static GENERATOR_API FString GetUEManagedProjectName();
	
	static GENERATOR_API FString GetUEManagedPath();
	
	static GENERATOR_API FString GetUEManagedProxyPath();

	static GENERATOR_API FString GetGameManagedProjectName();

	static GENERATOR_API FString GetGameManagedPath();

	static GENERATOR_API FString GetGameManagedProxyPath();
	
	static GENERATOR_API FString GetGenerationPath(const FString& InternalScriptPath);

	static GENERATOR_API void BeginCache();

	static GENERATOR_API void EndCache();
};

struct FScopedGeneratorPathsCache
{
	FScopedGeneratorPathsCache() { FGeneratorPaths::BeginCache(); }
	~FScopedGeneratorPathsCache() { FGeneratorPaths::EndCache(); }
};