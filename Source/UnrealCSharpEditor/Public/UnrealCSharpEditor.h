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
	void RegisterMenus();

public:
	static void Generator();

private:
	TSharedPtr<class FUnrealCSharpToolBar> UnrealCSharpToolBar;

	FEditorListener EditorListener;
};
