#include "Delegate/FUnrealCSharpModuleDelegates.h"

auto FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleActive() -> FOnUnrealCSharpModuleActive&
{
	static FOnUnrealCSharpModuleActive OnUnrealCSharpModuleActive;

	return OnUnrealCSharpModuleActive;
}

auto FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleInActive() -> FOnUnrealCSharpModuleInActive&
{
	static FOnUnrealCSharpModuleInActive OnUnrealCSharpModuleInActive;

	return OnUnrealCSharpModuleInActive;
}

auto FUnrealCSharpModuleDelegates::GetOnCSharpEnvironmentInitialize() -> FOnCSharpEnvironmentInitialize&
{
	static FOnCSharpEnvironmentInitialize OnCSharpEnvironmentInitialize;

	return OnCSharpEnvironmentInitialize;
}
