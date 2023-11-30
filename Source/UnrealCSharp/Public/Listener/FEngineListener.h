#pragma once

class FEngineListener
{
public:
	FEngineListener();

	~FEngineListener();

private:
#if WITH_EDITOR
	void OnPreBeginPIE(const bool);

	void OnPostPIEStarted(const bool);

	void OnCancelPIE();

#else
	void OnPostEngineInit();

	void OnPreExit();
#endif

private:
#if WITH_EDITOR
	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPostPIEStartedDelegateHandle;

	FDelegateHandle OnCancelPIEDelegateHandle;

#else
	FDelegateHandle OnPostEngineInitHandle;

	FDelegateHandle OnPreExitHandle;
#endif
};
