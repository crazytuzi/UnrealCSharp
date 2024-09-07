// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Listener/FEditorListener.h"
#include "Modules/ModuleManager.h"

class FUnrealCSharpEditorModule final : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonClicked() const;

private:
	void OnPostEngineInit();

private:
	void RegisterMenus();

public:
	static void UpdatePackagingSettings();

	static void Generator();

private:
	TSharedPtr<class FUnrealCSharpPlayToolBar> UnrealCSharpPlayToolBar;

	TSharedPtr<class FUnrealCSharpBlueprintToolBar> UnrealCSharpBlueprintToolBar;

	FDelegateHandle OnPostEngineInitDelegateHandle;

	TUniquePtr<FAutoConsoleCommand> CodeAnalysisConsoleCommand;

	TUniquePtr<FAutoConsoleCommand> SolutionGeneratorConsoleCommand;

	TUniquePtr<FAutoConsoleCommand> CompileConsoleCommand;

	TUniquePtr<FAutoConsoleCommand> GeneratorConsoleCommand;

	FEditorListener EditorListener;
};
