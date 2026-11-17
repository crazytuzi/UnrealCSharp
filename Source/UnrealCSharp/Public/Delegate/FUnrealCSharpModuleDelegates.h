#pragma once

class FUnrealCSharpModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleActive);

	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpModuleInActive);

	DECLARE_MULTICAST_DELEGATE(FOnCSharpEnvironmentInitialize);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCSharpClassBinding, UClass*);

	static FOnUnrealCSharpModuleActive& GetOnUnrealCSharpModuleActive();

	static FOnUnrealCSharpModuleInActive& GetOnUnrealCSharpModuleInActive();

	static FOnCSharpEnvironmentInitialize& GetOnCSharpEnvironmentInitialize();

	static FOnCSharpClassBinding& GetOnCSharpClassBinding();
};
