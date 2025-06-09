#include "FCSharpCompilerRunnable.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Log/UnrealCSharpLog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "UEVersion.h"
#if UE_APP_STYLE_GET_BRUSH
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

void FCSharpCompilerRunnable::DoWork()
{
	Compile([&]()
	{
		FDynamicGenerator::Generator(FileChanges);

		FileChanges.Empty();
	});
}

void FCSharpCompilerRunnable::ImmediatelyDoWork()
{
	Compile([]()
	{
		FDynamicGenerator::Generator();
	});
}

void FCSharpCompilerRunnable::Compile(const TFunction<void()>& InFunction)
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (UnrealCSharpEditorSetting->EnableCompiled())
		{
			bIsCompiling = true;

			Compile();

			const auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
				[InFunction, this]()
				{
					if (!GExitPurge)
					{
						FUnrealCSharpCoreModuleDelegates::OnCompile.Broadcast(FileChanges);

						InFunction();
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

void FCSharpCompilerRunnable::Compile()
{
	if (!IFileManager::Get().FileExists(*FUnrealCSharpFunctionLibrary::GetGameProjectPath()))
	{
		return;
	}

	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		static const FName CompileStatusBackground("Blueprint.CompileStatus.Background");

		FNotificationInfo NotificationInfo(FText::FromString(TEXT("Compilation background")));

		NotificationInfo.bUseSuccessFailIcons = true;

#if UE_APP_STYLE_GET_BRUSH
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
		"publish \"%s\" --nologo -c Debug -o \"%s\""
	),
	                                          *FUnrealCSharpFunctionLibrary::GetGameProjectPath(),
	                                          *FUnrealCSharpFunctionLibrary::GetFullPublishDirectory()
	);

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FString Result;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	auto ProcessHandle = FPlatformProcess::CreateProc(
		*CompileTool,
		*CompileParam,
		false,
		true,
		true,
		&OutProcessID,
		1,
		nullptr,
		WritePipe,
		ReadPipe);

	while (ProcessHandle.IsValid() && FPlatformProcess::IsApplicationRunning(OutProcessID))
	{
		FPlatformProcess::Sleep(0.01f);

		Result.Append(FPlatformProcess::ReadPipe(ReadPipe));
	}

	FNotificationInfo* NotificationInfo{};

	auto ReturnCode = 0;

	if (FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode))
	{
		[[maybe_unused]] static const FName CompileStatusUnknown("Blueprint.CompileStatus.Overlay.Unknown");

		static const FName CompileStatusError("Blueprint.CompileStatus.Overlay.Error");

		static const FName CompileStatusGood("Blueprint.CompileStatus.Overlay.Good");

		[[maybe_unused]] static const FName CompileStatusWarning("Blueprint.CompileStatus.Overlay.Warning");

		if (ReturnCode == 0)
		{
			NotificationInfo = new FNotificationInfo(FText::FromString(TEXT("Compilation succeeded")));

			NotificationInfo->bUseSuccessFailIcons = true;

#if UE_APP_STYLE_GET_BRUSH
			NotificationInfo->Image = FAppStyle::GetBrush(CompileStatusGood);
#else
			NotificationInfo->Image = FEditorStyle::GetBrush(CompileStatusGood);
#endif
		}
		else
		{
			NotificationInfo = new FNotificationInfo(FText::FromString(TEXT("Compilation failed")));

			NotificationInfo->bUseSuccessFailIcons = true;

#if UE_APP_STYLE_GET_BRUSH
			NotificationInfo->Image = FAppStyle::GetBrush(CompileStatusError);
#else
			NotificationInfo->Image = FEditorStyle::GetBrush(CompileStatusError);
#endif

			UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *Result);
		}
	}

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);

	FPlatformProcess::CloseProc(ProcessHandle);

	AsyncTask(ENamedThreads::GameThread, [this, NotificationInfo]()
	{
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
