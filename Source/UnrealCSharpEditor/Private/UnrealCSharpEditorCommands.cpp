// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpEditorCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorModule"

void FUnrealCSharpEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "UnrealCSharpEditor", "Execute UnrealCSharpEditor action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
