#include "FCSharpCompiler.h"
#include "FCSharpCompilerRunnable.h"

FCSharpCompiler::FCSharpCompiler():
	Runnable(nullptr),
	Thread(nullptr)
{
	Runnable = new FCSharpCompilerRunnable();

	Thread = FRunnableThread::Create(Runnable, TEXT("CSharpCompiler"));
}

FCSharpCompiler::~FCSharpCompiler()
{
	if (Thread != nullptr)
	{
		Thread->Kill(true);

		delete Thread;

		Thread = nullptr;

		delete Runnable;

		Runnable = nullptr;
	}
}

FCSharpCompiler& FCSharpCompiler::Get()
{
	static FCSharpCompiler Compiler;

	return Compiler;
}

void FCSharpCompiler::Compile() const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask();
	}
}

void FCSharpCompiler::ImmediatelyCompile(const bool bForceCompileInterop) const
{
	if (Runnable != nullptr)
	{
		Runnable->ImmediatelyDoWork(bForceCompileInterop);
	}
}

void FCSharpCompiler::Compile(const TArray<FFileChangeData>& InFileChangeData) const
{
	if (Runnable != nullptr)
	{
		Runnable->EnqueueTask(InFileChangeData);
	}
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

bool FCSharpCompiler::IsCompiling() const
{
	return Runnable != nullptr ? Runnable->IsCompiling() : false;
}

FString FCSharpCompiler::GetCompileProgress() const
{
	return Runnable != nullptr ? Runnable->GetCompileProgress() : TEXT("");
}
