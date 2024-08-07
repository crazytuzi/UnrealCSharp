#include "Listener/FEngineListener.h"
#include "UnrealCSharp.h"

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
	FUnrealCSharpModule::Get().SetActive(true);
}

void FEngineListener::OnPostPIEStarted(const bool)
{
}

void FEngineListener::OnCancelPIE()
{
	FUnrealCSharpModule::Get().SetActive(false);
}

#else
void FEngineListener::OnPostEngineInit()
{
	FUnrealCSharpModule::Get().SetActive(true);
}

void FEngineListener::OnPreExit()
{
	FUnrealCSharpModule::Get().SetActive(false);
}
#endif
