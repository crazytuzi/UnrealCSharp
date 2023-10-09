// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpEditorCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorModule"

void FUnrealCSharpEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "UnrealCSharpEditor", "Execute UnrealCSharpEditor action",
	           EUserInterfaceActionType::Button, FInputGesture());

	UI_COMMAND(OpenEditorSettings, "Open Editor Settings", "Open UnrealCSharpEditor Settings action",
	           EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
