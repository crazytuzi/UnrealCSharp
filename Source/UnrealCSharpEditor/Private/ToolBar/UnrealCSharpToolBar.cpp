#include "ToolBar/UnrealCSharpToolBar.h"
#include "ISettingsModule.h"
#include "ToolMenus.h"
#include "UnrealCSharpEditor.h"
#include "UnrealCSharpEditorCommands.h"
#include "UEVersion.h"

#define LOCTEXT_NAMESPACE "UnrealCSharpToolBar"

FUnrealCSharpToolBar::FUnrealCSharpToolBar()
	: PluginCommands(MakeShared<FUICommandList>())
{
	BuildAction();
}

void FUnrealCSharpToolBar::Initialize()
{
#if UE_TOOL_MENU
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
#else
	auto Extender = MakeShared<FExtender>);
	
	Extender->AddToolBarExtension("Settings", EExtensionHook::After, CommandList,
								  FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
								  {
									  Builder.BeginSection(NAME_None);
								  	
									  Builder.AddComboButton(FUIAction(),
															 FOnGetContent::CreateRaw(this, &FUnrealCSharpToolBar::GenerateGameTableSettingsMenu),
															 LOCTEXT("UnrealCSharpEditor_Label", "UnrealCSharpEditor"),
															 LOCTEXT("UnrealCSharpEditor_ToolTip", "UnrealCSharpEditor"),
															 FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction")
									  );
								  	
									  Builder.EndSection();
								  })
	);
	
	auto& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(Extender);
#endif
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
}

TSharedRef<SWidget> FUnrealCSharpToolBar::GenerateToolBarMenu()
{
	const FUnrealCSharpEditorCommands& Commands = FUnrealCSharpEditorCommands::Get();

	FMenuBuilder MenuBuilder(true, PluginCommands);

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("Section_Action", "Action"));

	MenuBuilder.AddMenuEntry(Commands.PluginAction, NAME_None, LOCTEXT("GeneratorCode", "Generator Code"));

	MenuBuilder.EndSection();

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("Section_Help", "Help"));

	MenuBuilder.AddMenuEntry(Commands.OpenEditorSettings, NAME_None, LOCTEXT("OpenEditorSettings", "Open Settings"));

	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

#undef LOCTEXT_NAMESPACE
