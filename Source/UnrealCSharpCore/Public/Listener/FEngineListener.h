#pragma once

#include "ModuleDescriptor.h"

class UNREALCSHARPCORE_API FEngineListener
{
public:
	FEngineListener();

	~FEngineListener();

#if WITH_EDITOR
public:
	static void OnPreBeginPIE(const bool);
#endif

private:
	void OnLoadingPhaseComplete(ELoadingPhase::Type LoadingPhase, bool bSuccess);

#if WITH_EDITOR
	void OnPostEngineInit();
#endif

	void OnPreExit();

	static void SetActive(bool InbIsActive);

	FDelegateHandle OnLoadingPhaseCompleteHandle;

#if WITH_EDITOR
	FDelegateHandle OnPostEngineInitHandle;
#endif

	FDelegateHandle OnPreExitHandle;
};
