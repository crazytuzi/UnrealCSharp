#pragma once

#if !WITH_EDITOR
#include "ModuleDescriptor.h"
#endif

class UNREALCSHARPCORE_API FEngineListener
{
public:
	FEngineListener();

	~FEngineListener();

#if WITH_EDITOR
public:
	static void OnPreBeginPIE(const bool);

	static void OnCancelPIE();
#else
private:
	void OnLoadingPhaseComplete(ELoadingPhase::Type LoadingPhase, bool bSuccess);

	void OnPreExit();
#endif

	static void SetActive(bool InbIsActive);

#if !WITH_EDITOR
private:
	FDelegateHandle OnLoadingPhaseCompleteHandle;

	FDelegateHandle OnPreExitHandle;
#endif
};
