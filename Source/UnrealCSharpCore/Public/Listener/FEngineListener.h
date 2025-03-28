#pragma once

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
	void OnPostEngineInit();

	void OnPreExit();
#endif

#if !WITH_EDITOR
private:
	FDelegateHandle OnPostEngineInitHandle;

	FDelegateHandle OnPreExitHandle;
#endif
};
