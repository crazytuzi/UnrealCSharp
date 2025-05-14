// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharp.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#if !WITH_EDITOR
#include "Dynamic/FDynamicGenerator.h"
#endif

#define LOCTEXT_NAMESPACE "FUnrealCSharpModule"

void FUnrealCSharpModule::StartupModule()
{
	OnUnrealCSharpCoreModuleActiveDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.
		AddRaw(this, &FUnrealCSharpModule::OnUnrealCSharpCoreModuleActive);

	OnUnrealCSharpCoreModuleInActiveDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleInActive.
		AddRaw(this, &FUnrealCSharpModule::OnUnrealCSharpCoreModuleInActive);
}

void FUnrealCSharpModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (OnUnrealCSharpCoreModuleInActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleInActive.Remove(
			OnUnrealCSharpCoreModuleInActiveDelegateHandle);
	}

	if (OnUnrealCSharpCoreModuleActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.Remove(
			OnUnrealCSharpCoreModuleActiveDelegateHandle);
	}
}

void FUnrealCSharpModule::OnUnrealCSharpCoreModuleActive()
{
#if !WITH_EDITOR
	FDynamicGenerator::Generator();
#endif

	FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.Broadcast();
}

void FUnrealCSharpModule::OnUnrealCSharpCoreModuleInActive()
{
	FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Broadcast();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpModule, UnrealCSharp)
