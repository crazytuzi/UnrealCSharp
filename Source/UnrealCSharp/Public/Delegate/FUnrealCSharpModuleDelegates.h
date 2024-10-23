#pragma once

class FUnrealCSharpModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleActive);

	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleInActive);

	DECLARE_MULTICAST_DELEGATE(FOnCSharpEnvironmentInitialize);

	static UNREALCSHARP_API FOnUnrealCSharpModuleActive OnUnrealCSharpModuleActive;

	static UNREALCSHARP_API FOnUnrealCSharpModuleInActive OnUnrealCSharpModuleInActive;

	static UNREALCSHARP_API FOnCSharpEnvironmentInitialize OnCSharpEnvironmentInitialize;
};
