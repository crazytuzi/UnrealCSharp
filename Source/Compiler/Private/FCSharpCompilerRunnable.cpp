#include "FCSharpCompilerRunnable.h"
#include "UnrealCSharpCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Log/UnrealCSharpLog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "Widgets/Notifications/SNotificationList.h"
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
	bIsStopped(false),
	CompletedProjectCount(0),
	TotalProjectCount(0)
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

void FCSharpCompilerRunnable::GetCompileProgress(FString& OutMessage, float& OutFraction) const
{
	FScopeLock ScopeLock(&ProgressCriticalSection);

	OutMessage = ProgressMessage;

	OutFraction = TotalProjectCount > 0
		              ? FMath::Clamp(static_cast<float>(CompletedProjectCount) / TotalProjectCount, 0.0f, 1.0f)
		              : 0.0f;
}

void FCSharpCompilerRunnable::ResetCompileProgress(const FString& InMessage)
{
	FScopeLock ScopeLock(&ProgressCriticalSection);

	ProgressMessage = InMessage;

	ProgressOutputBuffer.Empty();

	CompletedProjectCount = 0;
}

void FCSharpCompilerRunnable::ParseCompileOutput(const FString& InOutput)
{
	FScopeLock ScopeLock(&ProgressCriticalSection);

	ProgressOutputBuffer.Append(InOutput);

	int32 NewlineIndex = INDEX_NONE;

	while (ProgressOutputBuffer.FindChar(TEXT('\n'), NewlineIndex))
	{
		auto Line = ProgressOutputBuffer.Left(NewlineIndex);

		ProgressOutputBuffer.MidInline(NewlineIndex + 1);

		Line.TrimStartAndEndInline();

		if (Line.IsEmpty())
		{
			continue;
		}

		UE_LOG(LogUnrealCSharp, Display, TEXT("%s"), *Line);

		if (Line.Contains(TEXT(" -> ")))
		{
			++CompletedProjectCount;
		}

		ProgressMessage = Line;
	}
}

void FCSharpCompilerRunnable::DoWork()
{
	Compile([&]()
	{
		FDynamicGenerator::Generator(FileChanges);

		FileChanges.Empty();
	});
}

void FCSharpCompilerRunnable::ImmediatelyDoWork(const bool bForceCompileInterop)
{
	Compile([]()
	{
		FDynamicGenerator::Generator();
	}, true, bForceCompileInterop);
}

void FCSharpCompilerRunnable::Compile(const TFunction<void()>& InFunction, const bool bCompileInterop,
                                      const bool bForceCompileInterop)
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableCompiled())
		{
			bIsCompiling = true;

			ResetCompileProgress(TEXT("Preparing C# compilation..."));

			if (bCompileInterop)
			{
				CompileInterop(bForceCompileInterop);
			}

			Compile();

			const auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
				[InFunction, this]()
				{
					if (!GExitPurge)
					{
						auto& CoreModule = FUnrealCSharpCoreModule::Get();

						const auto bWasActive = CoreModule.IsActive();

						if (bWasActive)
						{
							CoreModule.SetActive(false);
						}

						FUnrealCSharpCoreModuleDelegates::OnCompile.Broadcast(FileChanges);

						InFunction();

						if (bWasActive)
						{
							CoreModule.SetActive(true);
						}
					}
				},
				TStatId(),
				nullptr,
				ENamedThreads::GameThread);

			FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);

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

void FCSharpCompilerRunnable::CompileInterop(const bool bForceCompileInterop)
{
	const auto InteropProjectPath = FUnrealCSharpFunctionLibrary::GetInteropProjectPath();

	if (!IFileManager::Get().FileExists(*InteropProjectPath))
	{
		return;
	}

	if (const auto InteropPath = FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath();
		bForceCompileInterop || !IFileManager::Get().FileExists(*InteropPath))
	{
		ResetCompileProgress(TEXT("Compiling Interop..."));

		static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

		const auto CompileParam = FString::Printf(TEXT(
			"build \"%s\" --nologo -c %s%s"
		),
		                                          *FUnrealCSharpFunctionLibrary::GetInteropProjectPath(),
		                                          *GetBuildConfiguration(),
		                                          bForceCompileInterop ? TEXT(" --no-incremental") : TEXT("")
		);

		FUnrealCSharpFunctionLibrary::SyncProcess(CompileTool, CompileParam,
		                                          [](const int32 InReturnCode, const FString& InResult)
		                                          {
			                                          if (InReturnCode != 0)
			                                          {
			                                          }
		                                          },
		                                          FPaths::GetPath(InteropProjectPath)
		);
	}
}

void FCSharpCompilerRunnable::Compile()
{
	if (!IFileManager::Get().FileExists(*FUnrealCSharpFunctionLibrary::GetGameProjectPath()))
	{
		return;
	}

	{
		TArray<FString> ProjectFiles;

		IFileManager::Get().FindFilesRecursive(ProjectFiles,
		                                       *FUnrealCSharpFunctionLibrary::GetFullScriptDirectory(),
		                                       TEXT("*.csproj"), true, false);

		FScopeLock ScopeLock(&ProgressCriticalSection);

		TotalProjectCount = FMath::Max(ProjectFiles.Num(), 1);

		CompletedProjectCount = 0;

		ProgressOutputBuffer.Empty();

		ProgressMessage = TEXT("Starting dotnet build...");
	}

	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		if (GExitPurge)
		{
			return;
		}

		static const FName CompileStatusBackground("Blueprint.CompileStatus.Background");

		FNotificationInfo NotificationInfo(FText::FromString(TEXT("Compilation background")));

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
	});

	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto CompileParam = FString::Printf(TEXT(
		"build \"%s\" --nologo -c %s"
	),
	                                          *FUnrealCSharpFunctionLibrary::GetGameProjectPath(),
	                                          *GetBuildConfiguration()
	);

	FNotificationInfo* NotificationInfo{};

	const auto OnComplete = [&NotificationInfo](const int32 InReturnCode, const FString& InResult)
	{
		[[maybe_unused]] static const FName CompileStatusUnknown("Blueprint.CompileStatus.Overlay.Unknown");

		static const FName CompileStatusError("Blueprint.CompileStatus.Overlay.Error");

		static const FName CompileStatusGood("Blueprint.CompileStatus.Overlay.Good");

		[[maybe_unused]] static const FName CompileStatusWarning("Blueprint.CompileStatus.Overlay.Warning");

		if (InReturnCode == 0)
		{
			FUnrealCSharpFunctionLibrary::TouchBuildStamp();

			NotificationInfo = new FNotificationInfo(FText::FromString(TEXT("Compilation succeeded")));

			NotificationInfo->bUseSuccessFailIcons = true;

#if UE_F_APP_STYLE_GET_BRUSH
			NotificationInfo->Image = FAppStyle::GetBrush(CompileStatusGood);
#else
			NotificationInfo->Image = FEditorStyle::GetBrush(CompileStatusGood);
#endif
		}
		else
		{
			NotificationInfo = new FNotificationInfo(FText::FromString(TEXT("Compilation failed")));

			NotificationInfo->bUseSuccessFailIcons = true;

#if UE_F_APP_STYLE_GET_BRUSH
			NotificationInfo->Image = FAppStyle::GetBrush(CompileStatusError);
#else
			NotificationInfo->Image = FEditorStyle::GetBrush(CompileStatusError);
#endif

			UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *InResult);
		}
	};

	FUnrealCSharpFunctionLibrary::SyncProcess(CompileTool, CompileParam, OnComplete, FString(),
	                                          [this](const FString& InOutput)
	                                          {
		                                          ParseCompileOutput(InOutput);
	                                          });

	AsyncTask(ENamedThreads::GameThread, [this, NotificationInfo]()
	{
		if (GExitPurge)
		{
			return;
		}

		if (NotificationItem.IsValid())
		{
			NotificationItem->Fadeout();

			NotificationItem.Reset();
		}

		if (NotificationInfo != nullptr)
		{
			NotificationInfo->bFireAndForget = true;

			NotificationInfo->FadeOutDuration = 2.0f;

			NotificationInfo->FadeInDuration = 0.5f;

			FSlateNotificationManager::Get().QueueNotification(NotificationInfo);
		}
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
