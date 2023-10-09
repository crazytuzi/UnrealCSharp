#pragma once

#include "CoreMinimal.h"

class FUnrealCSharpToolBar final
{
public:
	FUnrealCSharpToolBar();

public:
	void Initialize();

private:
	void BuildAction();

	TSharedRef<SWidget> GenerateToolBarMenu();

private:
	TSharedRef<FUICommandList> PluginCommands;
};
