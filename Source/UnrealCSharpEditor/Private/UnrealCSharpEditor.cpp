// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpEditor.h"
#include "FBlueprintGenerator.h"
#include "FClassGenerator.h"
#include "FCSharpCompiler.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "FSolutionGenerator.h"
#include "FBindingClassGenerator.h"
#include "FBindingEnumGenerator.h"
#include "UnrealCSharpEditorStyle.h"
#include "UnrealCSharpEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Internationalization/Culture.h"
#include "FCodeAnalysis.h"
#include "Misc/ScopedSlowTask.h"
#include "Mixin/FMixinGenerator.h"
#include "Setting/UnrealCSharpSetting.h"

static const FName UnrealCSharpEditorTabName("UnrealCSharpEditor");

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorModule"

void FUnrealCSharpEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FUnrealCSharpEditorStyle::Initialize();
	FUnrealCSharpEditorStyle::ReloadTextures();

	FUnrealCSharpEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FUnrealCSharpEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUnrealCSharpEditorModule::RegisterMenus));

	FUnrealCSharpSettingsHelper::RegisterSettings();
}

void FUnrealCSharpEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUnrealCSharpEditorStyle::Shutdown();

	FUnrealCSharpEditorCommands::Unregister();

	FUnrealCSharpSettingsHelper::UnregisterSettings();
}

void FUnrealCSharpEditorModule::PluginButtonClicked() const
{
	Generator();
}

void FUnrealCSharpEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FUnrealCSharpEditorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FUnrealCSharpEditorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FUnrealCSharpEditorModule::Generator()
{
	static FString DefaultCultureName = TEXT("en");

	const auto CurrentCultureName = FInternationalization::Get().GetCurrentCulture().Get().GetName();

	if (!CurrentCultureName.Equals(DefaultCultureName))
	{
		FInternationalization::Get().SetCurrentCulture(DefaultCultureName);
	}

	FScopedSlowTask SlowTask(12, LOCTEXT("GeneratingCodeAction", "Generating Code Action"));

	SlowTask.MakeDialog();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Code Analysis"));

	FCodeAnalysis::CodeAnalysis();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Code Analysis Generator"));

	FMixinGenerator::CodeAnalysisGenerator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Class Generator"));

	FClassGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Struct Generator"));

	FStructGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Enum Generator"));

	FEnumGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Blueprint Generator"));

	FBlueprintGenerator::Generator();

	FEnumGenerator::EmptyEnumUnderlyingType();

	if (!CurrentCultureName.Equals(DefaultCultureName))
	{
		FInternationalization::Get().SetCurrentCulture(CurrentCultureName);
	}

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Solution Generator"));

	FSolutionGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "BindingClass Generator"));

	FBindingClassGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "BindingEnum Generator"));

	FBindingEnumGenerator::Generator();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Garbage Collect"));

	CollectGarbage(RF_NoFlags, true);

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Compiler"));

	FCSharpCompiler::Get().ImmediatelyCompile();

	SlowTask.EnterProgressFrame(1, LOCTEXT("GeneratingCodeAction", "Completion"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpEditorModule, UnrealCSharpEditor)
