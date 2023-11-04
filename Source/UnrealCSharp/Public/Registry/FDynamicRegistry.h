#pragma once

class FDynamicRegistry
{
public:
	FDynamicRegistry();

	~FDynamicRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	void OnCSharpEnvironmentInitialize() const;

	void RegisterDynamic() const;

private:
	FDelegateHandle OnCSharpEnvironmentInitializeDelegateHandle;
};
