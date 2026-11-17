#include "CSharpBlueprintCallDescriptor.h"
#include "CSharpDelegateProxy.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Modules/ModuleManager.h"

class FUnrealCSharpBlueprintFunctionModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		OnModuleActiveHandle = FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleActive().AddStatic(
			&FUnrealCSharpBlueprintFunctionModule::ResetCache);

		OnModuleInActiveHandle = FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleInActive().AddStatic(
			&FUnrealCSharpBlueprintFunctionModule::ResetCache);
	}

	virtual void ShutdownModule() override
	{
		if (OnModuleInActiveHandle.IsValid())
		{
			FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleInActive().Remove(OnModuleInActiveHandle);
		}

		if (OnModuleActiveHandle.IsValid())
		{
			FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleActive().Remove(OnModuleActiveHandle);
		}

		ResetCache();

		UCSharpDelegateProxy::ResetRegistry();
	}

private:
	static void ResetCache()
	{
		FCSharpBlueprintCallCache::Get().Reset();
	}

	FDelegateHandle OnModuleActiveHandle;

	FDelegateHandle OnModuleInActiveHandle;
};

IMPLEMENT_MODULE(FUnrealCSharpBlueprintFunctionModule, UnrealCSharpBlueprintFunction)
