#include "Listener/FEngineListener.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"

FEngineListener::FEngineListener()
{
#if WITH_EDITOR
	OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &FEngineListener::OnPreBeginPIE);

	OnPostPIEStartedDelegateHandle = FEditorDelegates::PostPIEStarted.AddRaw(this, &FEngineListener::OnPostPIEStarted);

	OnCancelPIEDelegateHandle = FEditorDelegates::CancelPIE.AddRaw(this, &FEngineListener::OnCancelPIE);
#else
	OnPostEngineInitHandle = FCoreDelegates::OnPostEngineInit.AddRaw(this, &FEngineListener::OnPostEngineInit);

	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FEngineListener::OnPreExit);
#endif
}

FEngineListener::~FEngineListener()
{
#if WITH_EDITOR
	if (OnPreBeginPIEDelegateHandle.IsValid())
	{
		FEditorDelegates::PreBeginPIE.Remove(OnPreBeginPIEDelegateHandle);
	}

	if (OnPostPIEStartedDelegateHandle.IsValid())
	{
		FEditorDelegates::PostPIEStarted.Remove(OnPostPIEStartedDelegateHandle);
	}

	if (OnCancelPIEDelegateHandle.IsValid())
	{
		FEditorDelegates::CancelPIE.Remove(OnCancelPIEDelegateHandle);
	}
#else
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

void FEngineListener::OnPostPIEStarted(const bool)
{
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
