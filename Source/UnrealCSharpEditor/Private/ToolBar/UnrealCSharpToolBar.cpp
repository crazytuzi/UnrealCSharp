#include "ToolBar/UnrealCSharpToolBar.h"
#include "ISettingsModule.h"
#include "ToolMenus.h"
#include "UnrealCSharpEditor.h"
#include "UnrealCSharpEditorCommands.h"

#define LOCTEXT_NAMESPACE "UnrealCSharpToolBar"

FUnrealCSharpToolBar::FUnrealCSharpToolBar()
	: PluginCommands(MakeShared<FUICommandList>())
{
	BuildAction();
}

void FUnrealCSharpToolBar::Initialize()
{
	// 注册到菜单选项中
	const auto ToolMenus = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");

	auto& Section = ToolMenus->AddSection("UnrealCSharpEditor");

	Section.AddEntry(FToolMenuEntry::InitComboButton(
		"UnrealCSharpEditor",
		FUIAction(),
		FOnGetContent::CreateRaw(this, &FUnrealCSharpToolBar::GenerateToolBarMenu),
		LOCTEXT("UnrealCSharpEditor_Label", "UnrealCSharpEditor"),
		LOCTEXT("UnrealCSharpEditor_ToolTip", "UnrealCSharpEditor"),
		FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction")
	));
}

void FUnrealCSharpToolBar::BuildAction()
{
	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().PluginAction,
		FExecuteAction::CreateLambda([]
		{
			if (const auto UnrealCSharpEditorModule = FModuleManager::GetModulePtr<FUnrealCSharpEditorModule>(
				"UnrealCSharpEditor"))
			{
				UnrealCSharpEditorModule->PluginButtonClicked();
			}
		}),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenEditorSettings,
		FExecuteAction::CreateLambda([]
		{
			if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
			{
				SettingsModule->ShowViewer("Editor", "Plugins", "UnrealCSharpEditorSettings");
			}
		}), FCanExecuteAction());

	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenRuntimeSettings,
		FExecuteAction::CreateLambda([]
		{
			if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
			{
				SettingsModule->ShowViewer("Project", "Plugins", "UnrealCSharpSettings");
			}
		}), FCanExecuteAction());
}

TSharedRef<SWidget> FUnrealCSharpToolBar::GenerateToolBarMenu()
{
	const FUnrealCSharpEditorCommands& Commands = FUnrealCSharpEditorCommands::Get();

	FMenuBuilder MenuBuilder(true, PluginCommands);

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("Section_Action", "Action"));

	MenuBuilder.AddMenuEntry(Commands.PluginAction, NAME_None, LOCTEXT("GeneratorCode", "Generator Code"));

	MenuBuilder.EndSection();

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("Section_Help", "Help"));

	MenuBuilder.AddSubMenu(LOCTEXT("Section_SettingsMenu", "Settings"),
	                       LOCTEXT("Section_SettingsMenu_ToolTip", "UnrealCSharp Settings"),
	                       FNewMenuDelegate::CreateLambda([Commands](FMenuBuilder& SubMenuBuilder)
	                       {
		                       SubMenuBuilder.AddMenuEntry(Commands.OpenEditorSettings, NAME_None,
		                                                   LOCTEXT("OpenEditorSettings", "Editor"));

		                       SubMenuBuilder.AddMenuEntry(Commands.OpenRuntimeSettings, NAME_None,
		                                                   LOCTEXT("OpenRuntimeSettings", "Runtime"));
	                       }));

	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
