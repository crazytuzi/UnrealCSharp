// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpCore.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpCoreModule"

void FUnrealCSharpCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUnrealCSharpCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FUnrealCSharpCoreModule::SetActive(const bool InbIsActive)
{
	if (bIsActive != InbIsActive)
	{
		bIsActive = InbIsActive;

		if (InbIsActive)
		{
			FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.Broadcast();
		}
		else
		{
			FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleInActive.Broadcast();
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpCoreModule, UnrealCSharpCore)
