// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UnrealCSharpEditorStyle.h"

class FUnrealCSharpEditorCommands final : public TCommands<FUnrealCSharpEditorCommands>
{
public:
	FUnrealCSharpEditorCommands()
		: TCommands<FUnrealCSharpEditorCommands>(
			TEXT("UnrealCSharpEditor"),
			NSLOCTEXT("Contexts", "UnrealCSharpEditor", "UnrealCSharpEditor Plugin"),
			NAME_None,
			FUnrealCSharpEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> GeneratorCode;

	TSharedPtr<FUICommandInfo> OpenNewDynamicClassDialog;

	TSharedPtr<FUICommandInfo> OpenEditorSettings;

	TSharedPtr<FUICommandInfo> OpenRuntimeSettings;

	TSharedPtr<FUICommandInfo> OpenFile;

	TSharedPtr<FUICommandInfo> CodeAnalysis;

	TSharedPtr<FUICommandInfo> OverrideBlueprint;
};
