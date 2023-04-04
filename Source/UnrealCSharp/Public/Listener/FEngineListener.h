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

	void OnEndPIE(const bool);

#else
	void OnPostEngineInit();

	void OnPreExit();
#endif

	void OnAsyncLoadingFlushUpdate();

private:
#if WITH_EDITOR
	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPostPIEStartedDelegateHandle;

	FDelegateHandle OnEndPIEDelegateHandle;

#else
	FDelegateHandle OnPostEngineInitHandle;

	FDelegateHandle OnPreExitHandle;
#endif

	FDelegateHandle OnAsyncLoadingFlushUpdateHandle;
};
