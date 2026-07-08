#pragma once

#if WITH_EDITOR
#include "IDirectoryWatcher.h"
#endif

class UNREALCSHARPCORE_API FUnrealCSharpCoreModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpCoreModuleActive);

	DECLARE_MULTICAST_DELEGATE(FOnUnrealCSharpCoreModuleInActive);

	DECLARE_MULTICAST_DELEGATE(FOnBeginGenerator);

	DECLARE_MULTICAST_DELEGATE(FOnEndGenerator);

	DECLARE_MULTICAST_DELEGATE(FOnUnloadAssemblies);

#if WITH_EDITOR
	DECLARE_MULTICAST_DELEGATE(FOnDynamicClassUpdated);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompile, const TArray<FFileChangeData>& InFileChangeData);
#endif

	static FOnUnrealCSharpCoreModuleActive OnUnrealCSharpCoreModuleActive;

	static FOnUnrealCSharpCoreModuleInActive OnUnrealCSharpCoreModuleInActive;

	static FOnBeginGenerator OnBeginGenerator;

	static FOnEndGenerator OnEndGenerator;

	static FOnUnloadAssemblies OnUnloadAssemblies;

#if WITH_EDITOR
	static FOnDynamicClassUpdated OnDynamicClassUpdated;

	static FOnCompile OnCompile;
#endif
};
