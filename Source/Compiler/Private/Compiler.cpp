// Copyright Epic Games, Inc. All Rights Reserved.

#include "Compiler.h"

#include "FCSharpCompiler.h"
#include "HAL/ThreadHeartBeat.h"
#include "HAL/ThreadManager.h"

#define LOCTEXT_NAMESPACE "FCompilerModule"

void FCompilerModule::StartupModule()
{
#if WITH_EDITOR
	FEditorDelegates::StartPIE.AddRaw(this, &FCompilerModule::OnStartPIE);
#endif

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCompilerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FCompilerModule::OnStartPIE(bool bSimulateInEditor)
{
	if (!bSimulateInEditor)
	{
		while (FCSharpCompiler::Get().IsCompiling())
		{
			FThreadHeartBeat::Get().HeartBeat();
			FPlatformProcess::SleepNoStats(0.0001f);
			FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
			FThreadManager::Get().Tick();
			FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCompilerModule, Compiler)