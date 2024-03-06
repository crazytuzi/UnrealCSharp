#pragma once

struct UNREALCSHARPCORE_API FMonoDomainInitializeParams
{
	FString Domain;

	FString AssemblyUtil;

	TArray<FString> Assemblies;

	FMonoDomainInitializeParams(const FString& InDomain, const FString& InAssemblyUtil,
	                            const TArray<FString>& InAssemblies):
		Domain(InDomain),
		AssemblyUtil(InAssemblyUtil),
		Assemblies(InAssemblies)
	{
	}
};
