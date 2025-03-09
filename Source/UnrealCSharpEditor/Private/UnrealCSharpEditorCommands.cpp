// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpEditorCommands.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorModule"

void FUnrealCSharpEditorCommands::RegisterCommands()
{
	UI_COMMAND(GeneratorCode, "Generator Code", "Generator Code Action",
	           EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(OpenNewDynamicClass, "Open New Dynamic Class", "Open New UnrealCSharp Dynamic Class",
	           EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(OpenEditorSettings, "Open Editor Settings", "Open UnrealCSharpEditor Settings Action",
	           EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(OpenRuntimeSettings, "Open Runtime Settings", "Open UnrealCSharpRuntime Settings Action",
	           EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(OpenFile, "Open File", "Open File Action",
	           EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(CodeAnalysis, "Code Analysis", "Code Analysis Action",
	           EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(OverrideBlueprint, "Override Blueprint", "Override Blueprint Action",
	           EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
