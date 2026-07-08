// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharp.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Environment/FCSharpEnvironment.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpModule"

void FUnrealCSharpModule::StartupModule()
{
	OnUnrealCSharpCoreModuleActiveDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.
		AddRaw(this, &FUnrealCSharpModule::OnUnrealCSharpCoreModuleActive);

	OnUnrealCSharpCoreModuleInActiveDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleInActive.
		AddRaw(this, &FUnrealCSharpModule::OnUnrealCSharpCoreModuleInActive);

	OnUnloadAssembliesDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnUnloadAssemblies.AddRaw(
		this, &FUnrealCSharpModule::OnUnloadAssemblies);
}

void FUnrealCSharpModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (OnUnloadAssembliesDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnUnloadAssemblies.Remove(OnUnloadAssembliesDelegateHandle);
	}

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
#if WITH_EDITOR
	if (IsRunningGame())
	{
		FDynamicGenerator::Generator();
	}
#else
	FDynamicGenerator::Generator();
#endif

	FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.Broadcast();
}

void FUnrealCSharpModule::OnUnrealCSharpCoreModuleInActive()
{
	FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Broadcast();
}

void FUnrealCSharpModule::OnUnloadAssemblies()
{
	FCSharpEnvironment::GetEnvironment().Deinitialize();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpModule, UnrealCSharp)
