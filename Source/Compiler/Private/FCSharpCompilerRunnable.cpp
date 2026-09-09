#include "FCSharpCompilerRunnable.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Log/UnrealCSharpLog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Containers/Ticker.h"
#include "Internationalization/Text.h"
#include "UEVersion.h"
#if UE_F_APP_STYLE_GET_BRUSH
#include "Styling/AppStyle.h"
#else
#include "EditorStyleSet.h"
#endif

FCSharpCompilerRunnable::FCSharpCompilerRunnable():
	Event(nullptr),
	bIsCompiling(false),
	bIsGenerating(false),
	bIsStopped(false)
{
	OnBeginGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.AddRaw(
		this, &FCSharpCompilerRunnable::OnBeginGenerator);

	OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
		this, &FCSharpCompilerRunnable::OnEndGenerator);
}

FCSharpCompilerRunnable::~FCSharpCompilerRunnable()
{
	if (OnEndGeneratorDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Remove(OnEndGeneratorDelegateHandle);
	}

	if (OnBeginGeneratorDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.Remove(OnBeginGeneratorDelegateHandle);
	}
}

bool FCSharpCompilerRunnable::Init()
{
	Event = FPlatformProcess::GetSynchEventFromPool(true);

	return FRunnable::Init();
}

uint32 FCSharpCompilerRunnable::Run()
{
	while (true)
	{
		if (bIsStopped)
		{
			return 0;
		}

		if (!bIsGenerating)
		{
			if (!Tasks.IsEmpty())
			{
				bool Task = false;

				{
					FScopeLock ScopeLock(&CriticalSection);

					if (!Tasks.IsEmpty())
					{
						Tasks.Dequeue(Task);
					}
				}

				if (Task == true)
				{
					DoWork();
				}
			}
			else
			{
				if (Event != nullptr)
				{
					Event->Wait();
				}
			}
		}
	}
}

void FCSharpCompilerRunnable::Stop()
{
	bIsStopped = true;

	if (Event != nullptr)
	{
		Event->Trigger();
	}
}

void FCSharpCompilerRunnable::Exit()
{
	if (Event != nullptr)
	{
		FPlatformProcess::ReturnSynchEventToPool(Event);

		Event = nullptr;
	}
}

void FCSharpCompilerRunnable::EnqueueTask()
{
	{
		FScopeLock ScopeLock(&CriticalSection);

		if (!Tasks.IsEmpty())
		{
			Tasks.Empty();
		}

		Tasks.Enqueue(true);
	}

	Event->Trigger();
}

void FCSharpCompilerRunnable::EnqueueTask(const TArray<FFileChangeData>& InFileChangeData)
{
	{
		FScopeLock ScopeLock(&CriticalSection);

		if (!Tasks.IsEmpty())
		{
			Tasks.Empty();
		}

		FileChanges.Append(InFileChangeData);

		Tasks.Enqueue(true);
	}

	Event->Trigger();
}

bool FCSharpCompilerRunnable::IsCompiling() const
{
	return bIsCompiling == true || !Tasks.IsEmpty();
}

FString FCSharpCompilerRunnable::GetCompileProgress() const
{
	return CompileProgress.GetStage();
}

void FCSharpCompilerRunnable::DoWork()
{
	Compile([](const TArray<FFileChangeData>& InFileChanges)
	{
		FDynamicGenerator::Generator(InFileChanges);
	});
}

void FCSharpCompilerRunnable::ImmediatelyDoWork(const bool bForceCompileInterop)
{
	Compile([](const TArray<FFileChangeData>&)
	{
		FDynamicGenerator::Generator();
	}, true, bForceCompileInterop, true);
}

void FCSharpCompilerRunnable::Compile(const TFunction<void(const TArray<FFileChangeData>&)>& InFunction,
                                      const bool bCompileInterop, const bool bForceCompileInterop,
                                      const bool bReloadImmediately)
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableCompiled())
		{
			bIsCompiling = true;

			CompileProgress.SetStage(FCSharpCompileProgress::StagePreparing);

			if (bCompileInterop && !CompileInterop(bForceCompileInterop))
			{
				CompileProgress.SetStage(FCSharpCompileProgress::StageFailed);

				ShowCompileResultNotification(false);

				bIsCompiling = false;

				return;
			}

			TArray<FFileChangeData> FileChangesSnapshot;

			const auto bSucceeded = Compile();

			if (bSucceeded)
			{
				FScopeLock ScopeLock(&CriticalSection);

				FileChangesSnapshot = MoveTemp(FileChanges);
			}

			FUnrealCSharpCoreModuleDelegates::OnCompile.Broadcast(bSucceeded);

			if (bSucceeded)
			{
				const auto bHasDynamicFileChanged = FDynamicGenerator::HasDynamicFileChanged(FileChangesSnapshot);

				const auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
					[InFunction, bReloadImmediately, bHasDynamicFileChanged, FileChangesSnapshot]()
					{
						if (GExitPurge)
						{
							return;
						}

						auto& UnrealCSharpCoreModule = FUnrealCSharpCoreModule::Get();

						if (UnrealCSharpCoreModule.IsLoaded() && (bReloadImmediately || bHasDynamicFileChanged))
						{
							UnrealCSharpCoreModule.Deactivate();

							InFunction(FileChangesSnapshot);

							UnrealCSharpCoreModule.Activate();
						}
						else
						{
							InFunction(FileChangesSnapshot);

							UnrealCSharpCoreModule.MarkOutdated();
						}
					},
					TStatId(),
					nullptr,
					ENamedThreads::GameThread);

				FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
			}

			bIsCompiling = false;
		}
	}
}

FString FCSharpCompilerRunnable::GetBuildConfiguration()
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		const auto Configuration = IsRunningCookCommandlet()
			                           ? UnrealCSharpEditorSetting->GetRuntimeConfiguration()
			                           : UnrealCSharpEditorSetting->GetEditorConfiguration();

		return Configuration == ESolutionConfiguration::Debug ? TEXT("Debug") : TEXT("Release");
	}

	return TEXT("Debug");
}

bool FCSharpCompilerRunnable::CompileInterop(const bool bForceCompileInterop)
{
	const auto InteropProjectPath = FUnrealCSharpFunctionLibrary::GetInteropProjectPath();

	if (!IFileManager::Get().FileExists(*InteropProjectPath))
	{
		return true;
	}

	if (const auto InteropPath = FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath();
		bForceCompileInterop || !IFileManager::Get().FileExists(*InteropPath))
	{
		CompileProgress.SetStage(FCSharpCompileProgress::StageCompilingInterop);

		static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

		const auto CompileParam = FString::Printf(TEXT(
			"build \"%s\" --nologo -c %s%s"
		),
		                                          *FUnrealCSharpFunctionLibrary::GetInteropProjectPath(),
		                                          *GetBuildConfiguration(),
		                                          bForceCompileInterop ? TEXT(" --no-incremental") : TEXT("")
		);

		auto bSucceeded = false;

		FUnrealCSharpFunctionLibrary::SyncProcess(CompileTool, CompileParam,
		                                          [this, &bSucceeded](const int32 InReturnCode, const FString& InResult)
		                                          {
			                                          bSucceeded = InReturnCode == 0;

			                                          CompileProgress.Flush();

			                                          if (!bSucceeded)
			                                          {
				                                          UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *InResult);
			                                          }
		                                          },
		                                          FPaths::GetPath(InteropProjectPath),
		                                          [this](const FString& InOutput)
		                                          {
			                                          CompileProgress.SetOutput(InOutput);
		                                          }
		);

		return bSucceeded;
	}

	return true;
}

bool FCSharpCompilerRunnable::Compile()
{
	if (!IFileManager::Get().FileExists(*FUnrealCSharpFunctionLibrary::GetGameProjectPath()))
	{
		return false;
	}

	CompileProgress.SetStage(FCSharpCompileProgress::StageCompilingUE);

	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		if (GExitPurge)
		{
			return;
		}

		static const FName CompileStatusBackground("Blueprint.CompileStatus.Background");

		const auto DefaultText = NSLOCTEXT("UnrealCSharp", "CompilingNotification", "Compiling Scripts");

		FNotificationInfo NotificationInfo(DefaultText);

		NotificationInfo.bUseSuccessFailIcons = true;

#if UE_F_APP_STYLE_GET_BRUSH
		NotificationInfo.Image = FAppStyle::GetBrush(CompileStatusBackground);
#else
		NotificationInfo.Image = FEditorStyle::GetBrush(CompileStatusBackground);
#endif

		NotificationInfo.bFireAndForget = true;

		NotificationInfo.ExpireDuration = 60.f;

		NotificationInfo.FadeOutDuration = 0.5f;

		NotificationInfo.FadeInDuration = 0.5f;

		NotificationItem = FSlateNotificationManager::Get().AddNotification(NotificationInfo);

		if (NotificationItem.IsValid())
		{
			FTSTicker::GetCoreTicker().RemoveTicker(ProgressTickerHandle);

			ProgressTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda(
					[this, DefaultText, LastText = FString()](float) mutable
					{
						if (GExitPurge || !NotificationItem.IsValid() || !IsCompiling())
						{
							return false;
						}

						const auto Stage = CompileProgress.GetStage();

						if (const auto Text = Stage.IsEmpty() ? DefaultText.ToString() : Stage;
							Text != LastText)
						{
							LastText = Text;

							NotificationItem->SetText(FText::FromString(Text));
						}

						return true;
					}));
		}
	});

	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CompileParam = FString::Printf(TEXT(
		"build \"%s\" --nologo -c %s"
	),
	                                          *FUnrealCSharpFunctionLibrary::GetGameProjectPath(),
	                                          *GetBuildConfiguration()
	);

	auto bSucceeded = false;

	const auto OnComplete = [this, &bSucceeded](const int32 InReturnCode, const FString& InResult)
	{
		bSucceeded = InReturnCode == 0;

		CompileProgress.Flush();

		CompileProgress.SetStage(bSucceeded
			                         ? FCSharpCompileProgress::StageSucceeded
			                         : FCSharpCompileProgress::StageFailed);

		if (!bSucceeded)
		{
			UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *InResult);
		}

		ShowCompileResultNotification(bSucceeded);
	};

	FUnrealCSharpFunctionLibrary::SyncProcess(CompileTool, CompileParam, OnComplete, FString(),
	                                          [this](const FString& InOutput)
	                                          {
		                                          CompileProgress.SetOutput(InOutput);
	                                          });

	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		if (GExitPurge)
		{
			return;
		}

		FTSTicker::GetCoreTicker().RemoveTicker(ProgressTickerHandle);

		if (NotificationItem.IsValid())
		{
			NotificationItem->Fadeout();

			NotificationItem.Reset();
		}
	});

	return bSucceeded;
}

void FCSharpCompilerRunnable::ShowCompileResultNotification(const bool bSucceeded) const
{
	AsyncTask(ENamedThreads::GameThread, [bSucceeded]()
	{
		if (GExitPurge)
		{
			return;
		}

		static const FName CompileStatusError("Blueprint.CompileStatus.Overlay.Error");

		static const FName CompileStatusGood("Blueprint.CompileStatus.Overlay.Good");

		const auto NotificationInfo = new FNotificationInfo(
			FText::FromString(bSucceeded ? TEXT("Compilation succeeded") : TEXT("Compilation failed")));

		NotificationInfo->bUseSuccessFailIcons = true;

#if UE_F_APP_STYLE_GET_BRUSH
		NotificationInfo->Image = FAppStyle::GetBrush(bSucceeded ? CompileStatusGood : CompileStatusError);
#else
		NotificationInfo->Image = FEditorStyle::GetBrush(bSucceeded ? CompileStatusGood : CompileStatusError);
#endif

		FSlateNotificationManager::Get().QueueNotification(NotificationInfo);
	});
}

void FCSharpCompilerRunnable::OnBeginGenerator()
{
	bIsGenerating = true;

	Tasks.Empty();

	FileChanges.Empty();
}

void FCSharpCompilerRunnable::OnEndGenerator()
{
	bIsGenerating = false;

	Tasks.Empty();

	FileChanges.Empty();
}
