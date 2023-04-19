#include "FCSharpCompilerRunnable.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Macro.h"

FString FCSharpCompilerRunnable::CompileTool;

FCSharpCompilerRunnable::FCSharpCompilerRunnable():
	Event(nullptr),
	bIsCompiling(false)
{
}

bool FCSharpCompilerRunnable::Init()
{
	CompileTool = FUnrealCSharpFunctionLibrary::GetCompileTool();

	Event = FPlatformProcess::CreateSynchEvent(true);

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

bool FCSharpCompilerRunnable::IsCompiling() const
{
	return bIsCompiling == true || !Tasks.IsEmpty();
}

void FCSharpCompilerRunnable::DoWork()
{
	bIsCompiling = true;

	Compile();

	Pdb2Mdb();

	bIsCompiling = false;
}

void FCSharpCompilerRunnable::Compile()
{
	const auto OutFile = FPaths::ConvertRelativePathToFull(FString::Printf(TEXT(
		"%sScript\\Script.log"
	),
	                                                                       *FPaths::ProjectDir()
	));

	FPlatformFileManager::Get().Get().GetPlatformFile().DeleteFile(*OutFile);

	const auto CompileParam = FPaths::ConvertRelativePathToFull(FString::Printf(TEXT(
		"%sScript\\Game\\Game.csproj /build \"Debug\" /Out %s"
	),
		*FPaths::ProjectDir(),
		*OutFile
	));

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

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
			FString Result;

			FFileHelper::LoadFileToString(Result, *OutFile);

			// @TODO
		}
	}
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
