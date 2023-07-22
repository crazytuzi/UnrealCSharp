#pragma once

class FUnrealCSharpModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleActive);

	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleInActive);

	DECLARE_MULTICAST_DELEGATE(FOnCSharpEnvironmentInitialize);

	static FOnUnrealCSharpModuleActive OnUnrealCSharpModuleActive;

	static FOnUnrealCSharpModuleInActive OnUnrealCSharpModuleInActive;

	static FOnCSharpEnvironmentInitialize OnCSharpEnvironmentInitialize;
};
