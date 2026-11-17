#include "CSharpBlueprintCallDescriptor.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Modules/ModuleManager.h"

class FUnrealCSharpBlueprintFunctionModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		// C# 域重载后反射指针全部失效，描述符缓存必须跟着清空
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
