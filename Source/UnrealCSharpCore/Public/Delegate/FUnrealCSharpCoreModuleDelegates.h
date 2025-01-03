#pragma once

class UNREALCSHARPCORE_API FUnrealCSharpCoreModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpCoreModuleActive);

	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpCoreModuleInActive);

	DECLARE_MULTICAST_DELEGATE(FOnBeginGenerator);

	DECLARE_MULTICAST_DELEGATE(FOnEndGenerator);

	DECLARE_MULTICAST_DELEGATE(FOnDynamicClassUpdated);

	static FOnUnrealCSharpCoreModuleActive OnUnrealCSharpCoreModuleActive;

	static FOnUnrealCSharpCoreModuleInActive OnUnrealCSharpCoreModuleInActive;

	static FOnBeginGenerator OnBeginGenerator;

	static FOnEndGenerator OnEndGenerator;

	static FOnDynamicClassUpdated OnDynamicClassUpdated;
};
