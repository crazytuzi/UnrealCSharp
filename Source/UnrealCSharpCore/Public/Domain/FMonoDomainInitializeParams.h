#pragma once

struct UNREALCSHARPCORE_API FMonoDomainInitializeParams
{
	FString Domain;

	TArray<FString> Assemblies;

	FMonoDomainInitializeParams(const FString& InDomain,
	                            const TArray<FString>& InAssemblies):
		Domain(InDomain),
		Assemblies(InAssemblies)
	{
	}
};
