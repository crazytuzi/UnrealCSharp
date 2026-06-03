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

	static void OnCancelPIE();
#endif

private:
	void OnLoadingPhaseComplete(ELoadingPhase::Type LoadingPhase, bool bSuccess);

	void OnPreExit();

	static void SetActive(bool InbIsActive);

	FDelegateHandle OnLoadingPhaseCompleteHandle;

	FDelegateHandle OnPreExitHandle;
};
