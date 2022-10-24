#pragma once

class FUnrealCSharpModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleActive);

	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleInActive);

	static FOnUnrealCSharpModuleActive OnUnrealCSharpModuleActive;

	static FOnUnrealCSharpModuleInActive OnUnrealCSharpModuleInActive;
};
