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

void FUnrealCSharpCoreModule::Activate()
{
	if (State == EState::Inactive)
	{
		State = EState::Active;

		FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.Broadcast();
	}
}

void FUnrealCSharpCoreModule::Deactivate()
{
	if (State != EState::Inactive)
	{
		State = EState::Inactive;

		FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleInActive.Broadcast();
	}
}

void FUnrealCSharpCoreModule::MarkOutdated()
{
	if (State == EState::Active)
	{
		State = EState::Outdated;
	}
}

bool FUnrealCSharpCoreModule::IsLoaded() const
{
	return State != EState::Inactive;
}

bool FUnrealCSharpCoreModule::IsActive() const
{
	return State == EState::Active;
}

bool FUnrealCSharpCoreModule::IsOutdated() const
{
	return State == EState::Outdated;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpCoreModule, UnrealCSharpCore)
