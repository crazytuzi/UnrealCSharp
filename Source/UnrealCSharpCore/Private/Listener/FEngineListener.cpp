#include "Listener/FEngineListener.h"
#include "Interfaces/IPluginManager.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Setting/UnrealCSharpSetting.h"

FEngineListener::FEngineListener()
{
	// 注意：不要在这里用 IsRunningGame() 做守卫。
	// 编辑器进程自身不算 IsRunningGame()，加了守卫会导致编辑器启动时永远不调用
	// SetActive(true)，模块 State 一直是 Inactive，进而：
	//   - FCSharpEnvironment 从未 Initialize()，注册表/反射环境不存在
	//   - 保存 C# 时 CompileInternal 的 IsLoaded() 为 false，只 MarkOutdated()，不会重载
	// 表现为"改动必须重启编辑器"或"保存两次才生效"。
	OnLoadingPhaseCompleteHandle = IPluginManager::Get().OnLoadingPhaseComplete().AddRaw(
		this, &FEngineListener::OnLoadingPhaseComplete);

	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FEngineListener::OnPreExit);
}

FEngineListener::~FEngineListener()
{
	if (OnPreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(OnPreExitHandle);
	}

	if (OnLoadingPhaseCompleteHandle.IsValid())
	{
		IPluginManager::Get().OnLoadingPhaseComplete().Remove(OnLoadingPhaseCompleteHandle);
	}
}

#if WITH_EDITOR
void FEngineListener::OnPreBeginPIE(const bool)
{
	auto& UnrealCSharpCoreModule = FUnrealCSharpCoreModule::Get();

	if (UnrealCSharpCoreModule.IsOutdated())
	{
		UnrealCSharpCoreModule.Deactivate();
	}

	UnrealCSharpCoreModule.Activate();
}
#endif

void FEngineListener::OnLoadingPhaseComplete(const ELoadingPhase::Type LoadingPhase, const bool bSuccess)
{
	if (bSuccess)
	{
		if (LoadingPhase == ELoadingPhase::Type::PostDefault)
		{
			SetActive(true);
		}
	}
}

void FEngineListener::OnPreExit()
{
	SetActive(false);
}

void FEngineListener::SetActive(const bool InbIsActive)
{
	if (InbIsActive)
	{
		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
#if WITH_EDITOR
			if (UnrealCSharpSetting->IsEnableImmediatelyActive() &&
				!FUnrealCSharpFunctionLibrary::IsScriptPublishOutdated())
#else
			if (UnrealCSharpSetting->IsEnableImmediatelyActive())
#endif
			{
				FUnrealCSharpCoreModule::Get().Activate();
			}
		}
	}
	else
	{
		FUnrealCSharpCoreModule::Get().Deactivate();
	}
}
