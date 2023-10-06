#pragma once

#include "CoreMinimal.h"


class FUnrealCharpToolBar
{
public:
	FUnrealCharpToolBar();
	virtual ~FUnrealCharpToolBar() = default;

	void Initialize();

	

	

private:
	void BuildAction();
	
	TSharedRef<SWidget> GenerateToolBarMenu();

	TSharedRef<FUICommandList> PluginCommands;
};
