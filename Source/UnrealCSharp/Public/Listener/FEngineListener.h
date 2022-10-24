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
#endif

private:
#if WITH_EDITOR
	FDelegateHandle OnPreBeginPIEDelegateHandle;

	FDelegateHandle OnPostPIEStartedDelegateHandle;

	FDelegateHandle OnEndPIEDelegateHandle;
#endif
};
