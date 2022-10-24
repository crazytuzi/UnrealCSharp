#include "Listener/FEngineListener.h"
#include "UnrealCSharp.h"

FEngineListener::FEngineListener()
{
#if WITH_EDITOR
	OnPreBeginPIEDelegateHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &FEngineListener::OnPreBeginPIE);

	OnPostPIEStartedDelegateHandle = FEditorDelegates::PostPIEStarted.AddRaw(this, &FEngineListener::OnPostPIEStarted);

	OnEndPIEDelegateHandle = FEditorDelegates::EndPIE.AddRaw(this, &FEngineListener::OnEndPIE);
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

	if (OnEndPIEDelegateHandle.IsValid())
	{
		FEditorDelegates::EndPIE.Remove(OnEndPIEDelegateHandle);
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

void FEngineListener::OnEndPIE(const bool)
{
	FUnrealCSharpModule::Get().SetActive(false);
}
#endif
