#include "Listener/FEngineListener.h"
#if !WITH_EDITOR
#include "Interfaces/IPluginManager.h"
#endif
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"

FEngineListener::FEngineListener()
{
#if !WITH_EDITOR
	OnLoadingPhaseCompleteHandle = IPluginManager::Get().OnLoadingPhaseComplete().AddRaw(
		this, &FEngineListener::OnLoadingPhaseComplete);

	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FEngineListener::OnPreExit);
#endif
}

FEngineListener::~FEngineListener()
{
#if !WITH_EDITOR
	if (OnPreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(OnPreExitHandle);
	}

	if (OnLoadingPhaseCompleteHandle.IsValid())
	{
		IPluginManager::Get().OnLoadingPhaseComplete().Remove(OnLoadingPhaseCompleteHandle);
	}
#endif
}

#if WITH_EDITOR
void FEngineListener::OnPreBeginPIE(const bool)
{
	SetActive(true);
}

void FEngineListener::OnCancelPIE()
{
	SetActive(false);
}
#else
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
#endif

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
