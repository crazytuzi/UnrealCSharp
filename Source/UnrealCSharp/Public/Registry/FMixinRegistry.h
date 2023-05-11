#pragma once

class FMixinRegistry
{
public:
	FMixinRegistry();

	~FMixinRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	void OnCSharpEnvironmentInitialize() const;

	void RegisterMixin() const;

private:
	FDelegateHandle OnCSharpEnvironmentInitializeDelegateHandle;
};
