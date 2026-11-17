#include "FCSharpCompiler.h"
#include "Misc/CoreDelegates.h"
#include "FCSharpCompilerRunnable.h"

FCSharpCompiler::FCSharpCompiler() :
	Runnable(nullptr),
	Thread(nullptr)
{
	Runnable = new FCSharpCompilerRunnable();

	Thread = FRunnableThread::Create(Runnable, TEXT("CSharpCompiler"));

	OnPreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FCSharpCompiler::OnPreExit);
}

FCSharpCompiler::~FCSharpCompiler()
{
	OnPreExit();

	if (Thread != nullptr)
	{
		delete Thread;

		Thread = nullptr;
	}

	if (Runnable != nullptr)
	{
		delete Runnable;

		Runnable = nullptr;
	}
}

FCSharpCompiler& FCSharpCompiler::Get()
{
	static FCSharpCompiler Compiler;

	return Compiler;
}

void FCSharpCompiler::AsyncCompile() const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask();
	}
}

void FCSharpCompiler::AsyncCompile(const TArray<FFileChangeData>& InFileChangeData) const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask(InFileChangeData);
	}
}

void FCSharpCompiler::EnqueueTask(const TFunction<void()>& InTask) const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask(InTask);
	}
}

bool FCSharpCompiler::SyncCompile() const
{
	return Runnable != nullptr ? Runnable->SyncCompile() : false;
}

void FCSharpCompiler::Compile(const TFunction<void()>& InFunction) const
{
	if (Runnable != nullptr)
	{
		Runnable->Compile([InFunction](const TArray<FFileChangeData>&)
		{
			InFunction();
		});
	}
}

void FCSharpCompiler::ImmediatelyCompile(const bool bForceCompileInterop) const
{
	if (Runnable != nullptr)
	{
		Runnable->ImmediatelyDoWork(bForceCompileInterop);
	}
}

bool FCSharpCompiler::IsCompiling() const
{
	return Runnable != nullptr ? Runnable->IsCompiling() : false;
}

FString FCSharpCompiler::GetCompileProgress() const
{
	return Runnable != nullptr ? Runnable->GetCompileProgress() : TEXT("");
}

void FCSharpCompiler::OnPreExit()
{
	if (OnPreExitHandle.IsValid())
	{
		FCoreDelegates::OnPreExit.Remove(OnPreExitHandle);

		OnPreExitHandle.Reset();

		if (Runnable != nullptr)
		{
			Runnable->Stop();
		}

		if (Thread != nullptr)
		{
			Thread->Kill(true);
		}
	}
}
