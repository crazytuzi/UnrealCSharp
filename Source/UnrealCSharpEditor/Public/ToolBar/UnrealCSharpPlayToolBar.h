#pragma once

#include "CoreMinimal.h"

class FUnrealCSharpPlayToolBar final
{
public:
	FUnrealCSharpPlayToolBar();

public:
	void Initialize();

	void Deinitialize();

private:
	void BuildAction();

	TSharedRef<SWidget> GeneratePlayToolBarMenu();

private:
	TSharedRef<FUICommandList> CommandList;
};
