#include "Listener/FEngineListener.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"

FEngineListener::FEngineListener()
{
#if !WITH_EDITOR
	OnPostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEngineListener::OnPostEngineInit);

	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FEngineListener::OnPreExit);
#endif
}

FEngineListener::~FEngineListener()
{
#if !WITH_EDITOR
	if (OnPostEngineInitHandle.IsValid())
	{
		FCoreDelegates::OnPostEngineInit.Remove(OnPostEngineInitHandle);
	}

	if (OnPreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(OnPreExitHandle);
	}
#endif
}

#if WITH_EDITOR
void FEngineListener::OnPreBeginPIE(const bool)
{
	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		if (UnrealCSharpSetting->IsEnableImmediatelyActive())
		{
			FUnrealCSharpCoreModule::Get().SetActive(true);
		}
	}
}

void FEngineListener::OnCancelPIE()
{
	FUnrealCSharpCoreModule::Get().SetActive(false);
}
#else
void FEngineListener::OnPostEngineInit()
{
	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<UUnrealCSharpSetting>())
	{
		if (UnrealCSharpSetting->IsEnableImmediatelyActive())
		{
			FUnrealCSharpCoreModule::Get().SetActive(true);
		}
	}
}

void FEngineListener::OnPreExit()
{
	FUnrealCSharpCoreModule::Get().SetActive(false);
}
#endif
