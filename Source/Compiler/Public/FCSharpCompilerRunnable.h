#pragma once

class FCSharpCompilerRunnable final : public FRunnable
{
public:
	FCSharpCompilerRunnable();

public:
	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;

	virtual void Exit() override;

public:
	void EnqueueTask();

	bool IsCompiling() const;

private:
	void DoWork();

	static void Compile();

	static FString GetCompileTool(const FString& ProductLineVersion = FString("2022"));

private:
	static FString CompileTool;

	TQueue<bool> Tasks;

	FCriticalSection CriticalSection;

	FEvent* Event;

	bool bIsCompiling;
};
