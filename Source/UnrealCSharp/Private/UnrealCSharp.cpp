// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharp.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpModule"

void FUnrealCSharpModule::StartupModule()
{
}

void FUnrealCSharpModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FUnrealCSharpModule::GetActive() const
{
	return bIsActive;
}

void FUnrealCSharpModule::SetActive(const bool InbIsActive)
{
	bIsActive = InbIsActive;

	if (InbIsActive)
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.Broadcast();
	}
	else
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Broadcast();
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpModule, UnrealCSharp)
