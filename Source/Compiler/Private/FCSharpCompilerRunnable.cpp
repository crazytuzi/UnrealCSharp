#include "FCSharpCompilerRunnable.h"

FString FCSharpCompilerRunnable::CompileTool;

FCSharpCompilerRunnable::FCSharpCompilerRunnable():
	Event(nullptr),
	bIsCompiling(false)
{
}

bool FCSharpCompilerRunnable::Init()
{
	CompileTool = GetCompileTool();

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

FString FCSharpCompilerRunnable::GetCompileTool(const FString& ProductLineVersion)
{
	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	const auto ProcessHandle = FPlatformProcess::CreateProc(
		TEXT("C:\\Program Files (x86)\\Microsoft Visual Studio\\Installer\\vswhere.exe"),
		TEXT("-legacy -prerelease -format json"),
		false,
		true,
		true,
		&OutProcessID,
		1,
		nullptr,
		WritePipe,
		ReadPipe);

	FString Result;

	while (ProcessHandle.IsValid() && FPlatformProcess::IsApplicationRunning(OutProcessID))
	{
		FPlatformProcess::Sleep(0.01f);

		auto Line = FPlatformProcess::ReadPipe(ReadPipe);

		if (Line.Len() > 0)
		{
			Result += Line;
		}
	}

	Result = Result.Replace(TEXT("\r\n"), TEXT(""));

	TArray<TSharedPtr<FJsonValue>> OutArray;

	const auto Reader = TJsonReaderFactory<>::Create(Result);

	FJsonSerializer::Deserialize(Reader, OutArray);

	for (const auto& Elem : OutArray)
	{
		if (Elem->AsObject()->GetObjectField("catalog")->GetStringField("productLineVersion") == ProductLineVersion)
		{
			return Elem->AsObject()->GetStringField("productPath");
		}
	}

	return TEXT("");
}
