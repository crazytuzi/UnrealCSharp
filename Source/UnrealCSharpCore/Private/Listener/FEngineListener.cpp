#include "Listener/FEngineListener.h"
#include "Interfaces/IPluginManager.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"
#include "UEVersion.h"

FEngineListener::FEngineListener()
{
#if WITH_EDITOR
	if (IsRunningGame())
	{
		OnLoadingPhaseCompleteHandle = IPluginManager::Get().OnLoadingPhaseComplete().AddRaw(
			this, &FEngineListener::OnLoadingPhaseComplete);
	}
	else if (!IsRunningCommandlet())
	{
#if UE_F_CORE_DELEGATES_GET_ON_POST_ENGINE_INIT
		OnPostEngineInitHandle = FCoreDelegates::GetOnPostEngineInit().AddRaw(
			this, &FEngineListener::OnPostEngineInit);
#else
		OnPostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddRaw(
			this, &FEngineListener::OnPostEngineInit);
#endif
	}
#else
	OnLoadingPhaseCompleteHandle = IPluginManager::Get().OnLoadingPhaseComplete().AddRaw(
		this, &FEngineListener::OnLoadingPhaseComplete);
#endif

	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FEngineListener::OnPreExit);
}

FEngineListener::~FEngineListener()
{
	if (OnPreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(OnPreExitHandle);
	}

#if WITH_EDITOR
	if (OnPostEngineInitHandle.IsValid())
	{
#if UE_F_CORE_DELEGATES_GET_ON_POST_ENGINE_INIT
		FCoreDelegates::GetOnPostEngineInit().Remove(OnPostEngineInitHandle);
#else
		FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitHandle);
#endif

		OnPostEngineInitHandle.Reset();
	}
#endif

	if (OnLoadingPhaseCompleteHandle.IsValid())
	{
		IPluginManager::Get().OnLoadingPhaseComplete().Remove(OnLoadingPhaseCompleteHandle);
	}
}

#if WITH_EDITOR
void FEngineListener::OnPreBeginPIE(const bool)
{
	auto& UnrealCSharpCoreModule = FUnrealCSharpCoreModule::Get();

	if (UnrealCSharpCoreModule.IsOutdated())
	{
		UnrealCSharpCoreModule.Deactivate();
	}

	UnrealCSharpCoreModule.Activate();
}
#endif

void FEngineListener::OnLoadingPhaseComplete(const ELoadingPhase::Type LoadingPhase, const bool bSuccess)
{
	if (bSuccess)
	{
		if (LoadingPhase == ELoadingPhase::Type::PostDefault)
		{
			SetActive(true);
		}
	}
}

#if WITH_EDITOR
void FEngineListener::OnPostEngineInit()
{
	SetActive(true);
}
#endif

void FEngineListener::OnPreExit()
{
	SetActive(false);
}

void FEngineListener::SetActive(const bool InbIsActive)
{
	if (InbIsActive)
	{
		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
#if WITH_EDITOR
			if (UnrealCSharpSetting->IsEnableImmediatelyActive() &&
				!FUnrealCSharpFunctionLibrary::IsScriptPublishOutdated())
#else
			if (UnrealCSharpSetting->IsEnableImmediatelyActive())
#endif
			{
				FUnrealCSharpCoreModule::Get().Activate();
			}
		}
	}
	else
	{
		FUnrealCSharpCoreModule::Get().Deactivate();
	}
}
