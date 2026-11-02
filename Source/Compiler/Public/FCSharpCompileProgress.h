#pragma once

#include "CoreMinimal.h"

class FCSharpCompileProgress
{
public:
	void SetStage(const FString& InStage);

	void SetOutput(const FString& InOutput);

	void Flush();

	FString GetStage() const;

public:
	static const TCHAR* const StagePreparing;

	static const TCHAR* const StageRestoring;

	static const TCHAR* const StageCompilingInterop;

	static const TCHAR* const StageCompilingUE;

	static const TCHAR* const StageCompilingGame;

	static const TCHAR* const StagePublishing;

	static const TCHAR* const StageSucceeded;

	static const TCHAR* const StageFailed;

private:
	enum class ECompilePhase : uint8
	{
		None,
		Interop,
		Game
	};

	FString ParseLine(const FString& InLine) const;

	void ProcessLine(const FString& InLine);

	mutable FCriticalSection CriticalSection;

	FString Stage;

	ECompilePhase CompilePhase = ECompilePhase::None;

	FString PendingOutput;
};
