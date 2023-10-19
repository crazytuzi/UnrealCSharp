#include "FCSharpCompilerRunnable.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "UEVersion.h"
#include "Dynamic/FDynamicGenerator.h"

FCSharpCompilerRunnable::FCSharpCompilerRunnable():
	Event(nullptr),
	bIsCompiling(false)
{
}

bool FCSharpCompilerRunnable::Init()
{
#if UE_PLATFORM_PROCESS_GET_SYNCH_EVENT_FROM_POOL
	Event = FPlatformProcess::GetSynchEventFromPool(true);
#else
	Event = FPlatformProcess::CreateSynchEvent(true);
#endif

	return FRunnable::Init();
}

uint32 FCSharpCompilerRunnable::Run()
{
	while (true)
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

void FCSharpCompilerRunnable::Stop()
{
	if (Event != nullptr)
	{
		FPlatformProcess::ReturnSynchEventToPool(Event);

		Event = nullptr;
	}
}

void FCSharpCompilerRunnable::Exit()
{
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

void FCSharpCompilerRunnable::EnqueueTask(const TArray<FFileChangeData>& FileChangeData)
{
	{
		FScopeLock ScopeLock(&CriticalSection);

		if (!Tasks.IsEmpty())
		{
			Tasks.Empty();
		}

		FileChanges.Append(FileChangeData);

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
	bIsCompiling = true;

	Compile();

	Pdb2Mdb();

	const auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady([&]()
	{
		FDynamicGenerator::Generator(FileChanges);

		FileChanges.Empty();
	}, TStatId(), nullptr, ENamedThreads::GameThread);

	FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);

	bIsCompiling = false;
}

void FCSharpCompilerRunnable::Compile()
{
	static auto CompileTool = FUnrealCSharpFunctionLibrary::GetDotNet();

	const auto OutDirectory = FString::Printf(TEXT(
		"%sScript"
	),
	                                          *FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir())
	);

	const auto CompileParam = FString::Printf(TEXT(
		"publish %sScript/Game/Game.csproj --nologo -c Debug -o %s"
	),
	                                          *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()),
	                                          *OutDirectory
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

	auto ReturnCode = 0;

	if (FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode))
	{
		if (ReturnCode == 0)
		{
			// @TODO
		}
		else
		{
			// @TODO
		}
	}

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);

	FPlatformProcess::CloseProc(ProcessHandle);
}

void FCSharpCompilerRunnable::Pdb2Mdb()
{
	auto OutProcessID = 0u;

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	static auto Pdb2MdbPath = TEXT("C:\\Program Files\\Mono\\lib\\mono\\4.5\\pdb2mdb.exe");

	const auto Pdb2MdbTasks = {
		FString::Printf(TEXT(
			"\"%s\" %s\\%s\\%s%s"
		),
		                Pdb2MdbPath,
		                *FPaths::ProjectContentDir(),
		                *SCRIPT,
		                *FUnrealCSharpFunctionLibrary::GetGameProjectName(),
		                *DLL_SUFFIX),
		FString::Printf(TEXT(
			"\"%s\" %s\\%s\\%s%s"
		),
		                Pdb2MdbPath,
		                *FPaths::ProjectContentDir(),
		                *SCRIPT,
		                *FUnrealCSharpFunctionLibrary::GetUEProjectName(),
		                *DLL_SUFFIX),
	};

	for (const auto& Params : Pdb2MdbTasks)
	{
		static auto MonoPath = TEXT("C:\\Program Files\\Mono\\bin\\mono.exe");

		auto ProcessHandle = FPlatformProcess::CreateProc(
			MonoPath,
			*Params,
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
		}
	}
}
