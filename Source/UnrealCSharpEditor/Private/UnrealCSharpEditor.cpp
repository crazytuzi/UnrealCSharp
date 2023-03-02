// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealCSharpEditor.h"
#include "FBlueprintGenerator.h"
#include "FClassGenerator.h"
#include "FCSharpCompiler.h"
#include "FEnumGenerator.h"
#include "FStructGenerator.h"
#include "FSolutionGenerator.h"
#include "ISettingsModule.h"
#include "UnrealCSharpEditorStyle.h"
#include "UnrealCSharpEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "UnrealCSharpSettings.h"

static const FName UnrealCSharpEditorTabName("UnrealCSharpEditor");

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorModule"

void FUnrealCSharpEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FUnrealCSharpEditorStyle::Initialize();
	FUnrealCSharpEditorStyle::ReloadTextures();
	RegisterSettings();
	FUnrealCSharpEditorCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FUnrealCSharpEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUnrealCSharpEditorModule::RegisterMenus));
}

void FUnrealCSharpEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUnrealCSharpEditorStyle::Shutdown();

	FUnrealCSharpEditorCommands::Unregister();
}

void FUnrealCSharpEditorModule::PluginButtonClicked()
{
	FClassGenerator::Generator();

	FStructGenerator::Generator();

	FEnumGenerator::Generator();

	FBlueprintGenerator::Generator();

	FEnumGenerator::EmptyEnumUnderlyingType();

	FSolutionGenerator::Generator();

	CollectGarbage(RF_NoFlags, true);

	FCSharpCompiler::Get().Compile();
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

void FUnrealCSharpEditorModule::RegisterSettings()
{
#if WITH_EDITOR
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (!SettingsModule)
		return;

	const auto Section = SettingsModule->RegisterSettings("Project", "Plugins", "UnrealCSharp",
	                                                      LOCTEXT("UnrealCSharpEditorSettingsName", "UnrealCSharp"),
	                                                      LOCTEXT("UnrealCSharpEditorSettingsDescription",
	                                                              "UnrealCSharp Runtime Settings"),
	                                                      GetMutableDefault<UnrealCSharpSettings>());
#endif

#if ENGINE_MAJOR_VERSION >=5 && !WITH_EDITOR
	// UE5强制重载ini
	FString UnrealCSharpIni = TEXT("UnrealCSharp");
	GConfig->LoadGlobalIniFile(UnrealCSharpIni, *UnrealCSharpIni, nullptr, true);
	UUnrealCSharpSettings::StaticClass()->GetDefaultObject()->ReloadConfig();
#endif
}
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealCSharpEditorModule, UnrealCSharpEditor)
