// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpCore.h"
#include "Dynamic/FDynamicGenerator.h"
#if WITH_EDITOR
#include "Setting/UnrealCSharpEditorSetting.h"
#include "Setting/UnrealCSharpSetting.h"
#endif

#define LOCTEXT_NAMESPACE "FUnrealCSharpCoreModule"

void FUnrealCSharpCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if WITH_EDITOR
	UUnrealCSharpEditorSetting::RegisterSettings();

	UUnrealCSharpSetting::RegisterSettings();
#endif

	FDynamicGenerator::Generator();
}

void FUnrealCSharpCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if WITH_EDITOR
	UUnrealCSharpEditorSetting::UnregisterSettings();

	UUnrealCSharpSetting::UnregisterSettings();
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpCoreModule, UnrealCSharpCore)
