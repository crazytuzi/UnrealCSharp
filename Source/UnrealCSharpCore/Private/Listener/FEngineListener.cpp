#include "Listener/FEngineListener.h"
#include "Interfaces/IPluginManager.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"

FEngineListener::FEngineListener()
{
	// Always deactivate on exit so listeners registered via PIE or the SetActive console command are removed before UObject array shutdown
	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FEngineListener::OnPreExit);

#if WITH_EDITOR
	if (!IsRunningGame())
	{
		return;
	}
#endif

	OnLoadingPhaseCompleteHandle = IPluginManager::Get().OnLoadingPhaseComplete().AddRaw(
		this, &FEngineListener::OnLoadingPhaseComplete);
}

FEngineListener::~FEngineListener()
{
	if (OnPreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(OnPreExitHandle);
	}

	if (OnLoadingPhaseCompleteHandle.IsValid())
	{
		IPluginManager::Get().OnLoadingPhaseComplete().Remove(OnLoadingPhaseCompleteHandle);
	}
}

#if WITH_EDITOR
void FEngineListener::OnPreBeginPIE(const bool)
{
	SetActive(true);
}

void FEngineListener::OnCancelPIE()
{
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
			if (UnrealCSharpSetting->IsEnableImmediatelyActive())
			{
				FUnrealCSharpCoreModule::Get().SetActive(true);
			}
		}
	}
	else
	{
		FUnrealCSharpCoreModule::Get().SetActive(false);
	}
}
