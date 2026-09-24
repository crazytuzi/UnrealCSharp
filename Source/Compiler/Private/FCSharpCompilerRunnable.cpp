#include "FCSharpCompilerRunnable.h"
#include "FCSharpCompiler.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Log/UnrealCSharpLog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Containers/Ticker.h"
#include "HAL/ThreadHeartBeat.h"
#include "Internationalization/Text.h"
#include "UEVersion.h"
#if UE_F_APP_STYLE_GET_BRUSH
#include "Styling/AppStyle.h"
#else
#include "EditorStyleSet.h"
#endif

FCSharpCompilerRunnable::FCSharpCompilerRunnable() :
	Event(nullptr),
	bIsCompiling(false),
	bIsGenerating(false),
	bIsStopped(false),
	bIsPending(false)
{
	OnBeginGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnBeginGenerator.AddRaw(
		this, &FCSharpCompilerRunnable::OnBeginGenerator);

	OnEndGeneratorDelegateHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddRaw(
		this, &FCSharpCompilerRunnable::OnEndGenerator);
}

FCSharpCompilerRunnable::~FCSharpCompilerRunnable()
{
	CompileNotification->bIsAlive = false;

	if (!GExitPurge)
	{
		if (CompileNotification->ProgressTickerHandle.IsValid())
		{
			FTSTicker::GetCoreTicker().RemoveTicker(CompileNotification->ProgressTickerHandle);

			CompileNotification->ProgressTickerHandle.Reset();
		}

		if (CompileNotification->NotificationItem.IsValid())
		{
			CompileNotification->NotificationItem->Fadeout();

			CompileNotification->NotificationItem.Reset();
		}
	}

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
	Event = FPlatformProcess::GetSynchEventFromPool(false);

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

		if (bIsGenerating)
		{
			if (Event != nullptr)
			{
				Event->Wait();
			}
		}
		else
		{
			if (bIsPending)
			{
				DoWork();
			}
			else if (Event != nullptr)
			{
				Event->Wait();
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

		bIsPending = true;
	}

	if (Event != nullptr)
	{
		Event->Trigger();
	}
}

void FCSharpCompilerRunnable::EnqueueTask(const TArray<FFileChangeData>& InFileChangeData)
{
	{
		FScopeLock ScopeLock(&CriticalSection);

		bIsPending = true;

		FileChanges.Append(InFileChangeData);
	}

	if (Event != nullptr)
	{
		Event->Trigger();
	}
}

bool FCSharpCompilerRunnable::IsCompiling() const
{
	FScopeLock ScopeLock(&CriticalSection);

	return bIsCompiling || bIsPending;
}

FString FCSharpCompilerRunnable::GetCompileProgress() const
{
	return CompileNotification->Progress.GetStage();
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

bool FCSharpCompilerRunnable::SyncCompile()
{
	AcquireCompile();

	auto bSucceeded = false;

	if (CompileInterop(false))
	{
		FString Result;

		bSucceeded = CompileGame(Result, [](const FString&)
		{
		});
	}

	ReleaseCompile();

	return bSucceeded;
}

void FCSharpCompilerRunnable::Compile(const TFunction<void(const TArray<FFileChangeData>&)>& InFunction,
                                      const bool bCompileInterop, const bool bForceCompileInterop,
                                      const bool bReloadImmediately)
{
	AcquireCompile();

	{
		FScopeLock ScopeLock(&CriticalSection);

		bIsPending = false;
	}

	CompileInternal(InFunction, bCompileInterop, bForceCompileInterop, bReloadImmediately);

	ReleaseCompile();
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
		CompileNotification->Progress.SetStage(FCSharpCompileProgress::StageCompilingInterop);

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

			                                          CompileNotification->Progress.Flush();

			                                          if (!bSucceeded)
			                                          {
				                                          UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *InResult);
			                                          }
		                                          },
		                                          FPaths::GetPath(InteropProjectPath),
		                                          [this](const FString& InOutput)
		                                          {
			                                          CompileNotification->Progress.SetOutput(InOutput);
		                                          },
		                                          [this]()
		                                          {
			                                          return bIsStopped || GExitPurge;
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

	CompileNotification->Progress.SetStage(FCSharpCompileProgress::StageCompilingUE);

	AsyncTask(ENamedThreads::GameThread, [Notification = CompileNotification]()
	{
		if (GExitPurge || !Notification->bIsAlive)
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

		Notification->NotificationItem = FSlateNotificationManager::Get().AddNotification(NotificationInfo);

		if (Notification->NotificationItem.IsValid())
		{
			Notification->bIsCompiling = true;

			FTSTicker::GetCoreTicker().RemoveTicker(Notification->ProgressTickerHandle);

			Notification->ProgressTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
				FTickerDelegate::CreateLambda(
					[Notification, DefaultText, LastText = FString()](float) mutable
					{
						if (GExitPurge || !Notification->bIsAlive ||
							!Notification->NotificationItem.IsValid() || !Notification->bIsCompiling)
						{
							return false;
						}

						const auto Stage = Notification->Progress.GetStage();

						if (const auto Text = Stage.IsEmpty() ? DefaultText.ToString() : Stage;
							Text != LastText)
						{
							LastText = Text;

							Notification->NotificationItem->SetText(FText::FromString(Text));
						}

						return true;
					}));
		}
	});

	FString Result;

	const auto bSucceeded = CompileGame(Result, [this](const FString& InOutput)
	{
		CompileNotification->Progress.SetOutput(InOutput);
	});

	CompileNotification->bIsCompiling = false;

	CompileNotification->Progress.Flush();

	CompileNotification->Progress.SetStage(bSucceeded
		                                       ? FCSharpCompileProgress::StageSucceeded
		                                       : FCSharpCompileProgress::StageFailed);

	if (!bSucceeded)
	{
		UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *Result);
	}

	ShowCompileResultNotification(bSucceeded);

	AsyncTask(ENamedThreads::GameThread, [Notification = CompileNotification]()
	{
		if (GExitPurge || !Notification->bIsAlive)
		{
			return;
		}

		if (Notification->ProgressTickerHandle.IsValid())
		{
			FTSTicker::GetCoreTicker().RemoveTicker(Notification->ProgressTickerHandle);

			Notification->ProgressTickerHandle.Reset();
		}

		if (Notification->NotificationItem.IsValid())
		{
			Notification->NotificationItem->Fadeout();

			Notification->NotificationItem.Reset();
		}
	});

	return bSucceeded;
}

bool FCSharpCompilerRunnable::CompileGame(FString& OutResult, const TFunction<void(const FString&)>& InOnOutput)
{
	if (!IFileManager::Get().FileExists(*FUnrealCSharpFunctionLibrary::GetGameProjectPath()))
	{
		return false;
	}

	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CompileParam = FString::Printf(TEXT(
		"build \"%s\" --nologo -c %s"
	),
	                                          *FUnrealCSharpFunctionLibrary::GetGameProjectPath(),
	                                          *GetBuildConfiguration()
	);

	auto bSucceeded = false;

	const auto OnComplete = [&bSucceeded, &OutResult](const int32 InReturnCode, const FString& InResult)
	{
		bSucceeded = InReturnCode == 0;

		OutResult = InResult;
	};

	FUnrealCSharpFunctionLibrary::SyncProcess(CompileTool, CompileParam, OnComplete, FString(), InOnOutput,
	                                          [this]()
	                                          {
		                                          return bIsStopped || GExitPurge;
	                                          });

	return bSucceeded;
}

void FCSharpCompilerRunnable::CompileInternal(const TFunction<void(const TArray<FFileChangeData>&)>& InFunction,
                                              const bool bCompileInterop, const bool bForceCompileInterop,
                                              const bool bReloadImmediately)
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableCompiled())
		{
			CompileNotification->Progress.SetStage(FCSharpCompileProgress::StagePreparing);

			if (bCompileInterop && !CompileInterop(bForceCompileInterop))
			{
				CompileNotification->Progress.SetStage(FCSharpCompileProgress::StageFailed);

				ShowCompileResultNotification(false);

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

				const auto Reload = [InFunction, bReloadImmediately, bHasDynamicFileChanged, FileChangesSnapshot]()
				{
					if (GExitPurge)
					{
						return;
					}

					auto& UnrealCSharpCoreModule = FUnrealCSharpCoreModule::Get();

					if (GIsPlayInEditorWorld)
					{
						UnrealCSharpCoreModule.MarkOutdated();

						return;
					}

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
				};

				const auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
					Reload,
					TStatId(),
					nullptr,
					ENamedThreads::GameThread);

				if (!IsInGameThread())
				{
					while (!Task->IsComplete() && !bIsStopped && !GExitPurge)
					{
						FPlatformProcess::SleepNoStats(FCSharpCompiler::PollIntervalSeconds);
					}
				}
			}
		}
	}
}

void FCSharpCompilerRunnable::AcquireCompile()
{
	while (true)
	{
		{
			FScopeLock ScopeLock(&CriticalSection);

			if (!bIsCompiling)
			{
				bIsCompiling = true;

				break;
			}
		}

		if (IsInGameThread())
		{
			FThreadHeartBeat::Get().HeartBeat();

			FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		}

		FPlatformProcess::SleepNoStats(FCSharpCompiler::PollIntervalSeconds);
	}
}

void FCSharpCompilerRunnable::ReleaseCompile()
{
	FScopeLock ScopeLock(&CriticalSection);

	bIsCompiling = false;
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

	FScopeLock ScopeLock(&CriticalSection);

	bIsPending = false;

	FileChanges.Empty();
}

void FCSharpCompilerRunnable::OnEndGenerator()
{
	bIsGenerating = false;

	{
		FScopeLock ScopeLock(&CriticalSection);

		bIsPending = false;

		FileChanges.Empty();
	}

	if (Event != nullptr)
	{
		Event->Trigger();
	}
}
