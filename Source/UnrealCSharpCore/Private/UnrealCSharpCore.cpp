// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpCore.h"
#if WITH_EDITOR
#include "Setting/UnrealCSharpEditorSetting.h"
#endif

#define LOCTEXT_NAMESPACE "FUnrealCSharpCoreModule"

void FUnrealCSharpCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if WITH_EDITOR
	UUnrealCSharpEditorSetting::RegisterSettings();
#endif
}

void FUnrealCSharpCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if WITH_EDITOR
	UUnrealCSharpEditorSetting::UnregisterSettings();
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpCoreModule, UnrealCSharpCore)
