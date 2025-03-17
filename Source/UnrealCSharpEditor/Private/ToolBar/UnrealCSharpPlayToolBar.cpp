#include "ToolBar/UnrealCSharpPlayToolBar.h"
#include "ISettingsModule.h"
#include "ToolMenus.h"
#include "UnrealCSharpEditor.h"
#include "UnrealCSharpEditorCommands.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "NewClass/DynamicNewClassUtils.h"

#define LOCTEXT_NAMESPACE "UnrealCSharpPlayToolBar"

FUnrealCSharpPlayToolBar::FUnrealCSharpPlayToolBar()
	: CommandList(MakeShared<FUICommandList>())
{
	BuildAction();
}

void FUnrealCSharpPlayToolBar::Initialize()
{
	const auto PlayToolBar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");

	auto& EditorSection = PlayToolBar->AddSection("UnrealCSharpEditor");

	EditorSection.AddEntry(FToolMenuEntry::InitComboButton(
		"UnrealCSharpEditor",
		FUIAction(),
		FOnGetContent::CreateRaw(this, &FUnrealCSharpPlayToolBar::GeneratePlayToolBarMenu),
		LOCTEXT("UnrealCSharpEditor_Label", "UnrealCSharp"),
		LOCTEXT("UnrealCSharpEditor_ToolTip", "UnrealCSharp"),
		FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction")
	));
}

void FUnrealCSharpPlayToolBar::Deinitialize()
{
}

void FUnrealCSharpPlayToolBar::BuildAction()
{
	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().GeneratorCode,
		FExecuteAction::CreateLambda([]
		{
			if (const auto UnrealCSharpEditorModule = FModuleManager::GetModulePtr<FUnrealCSharpEditorModule>(
				"UnrealCSharpEditor"))
			{
				UnrealCSharpEditorModule->PluginButtonClicked();
			}
		}), FCanExecuteAction());

	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenNewDynamicClass,
		FExecuteAction::CreateLambda([]
		{
			FDynamicNewClassUtils::OpenAddDynamicClassToProjectDialog(
				FUnrealCSharpFunctionLibrary::GetGameDirectory());
		}), FCanExecuteAction());

	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenEditorSettings,
		FExecuteAction::CreateLambda([]
		{
			if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
			{
				SettingsModule->ShowViewer("Editor", "Plugins", "UnrealCSharpEditorSettings");
			}
		}), FCanExecuteAction());

	CommandList->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenRuntimeSettings,
		FExecuteAction::CreateLambda([]
		{
			if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
			{
				SettingsModule->ShowViewer("Project", "Plugins", "UnrealCSharpSettings");
			}
		}), FCanExecuteAction());
}

TSharedRef<SWidget> FUnrealCSharpPlayToolBar::GeneratePlayToolBarMenu()
{
	const FUnrealCSharpEditorCommands& Commands = FUnrealCSharpEditorCommands::Get();

	FMenuBuilder MenuBuilder(true, CommandList);

	MenuBuilder.BeginSection(NAME_None);

	MenuBuilder.AddMenuEntry(Commands.GeneratorCode, NAME_None,
	                         LOCTEXT("GeneratorCode", "Generator Code"));

	MenuBuilder.AddMenuEntry(Commands.OpenNewDynamicClass, NAME_None,
	                         LOCTEXT("OpenNewDynamicClass", "Open NewDynamicClass"));

	MenuBuilder.AddMenuEntry(Commands.OpenEditorSettings, NAME_None,
	                         LOCTEXT("OpenEditorSettings", "Open EditorSettings"));

	MenuBuilder.AddMenuEntry(Commands.OpenRuntimeSettings, NAME_None,
	                         LOCTEXT("OpenRuntimeSettings", "Open RuntimeSettings"));

	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
