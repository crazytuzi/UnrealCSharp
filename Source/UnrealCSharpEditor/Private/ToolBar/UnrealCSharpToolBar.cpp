#include "ToolBar/UnrealCSharpToolBar.h"

#include "ISettingsModule.h"
#include "UnrealCSharpEditor.h"
#include "UnrealCSharpEditorCommands.h"


#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include "Windows/MinWindows.h"
#include <shellapi.h>
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#endif


#define LOCTEXT_NAMESPACE "UnrealCharpToolBar"


FUnrealCharpToolBar::FUnrealCharpToolBar()
	: PluginCommands(MakeShareable(new FUICommandList))
{
	BuildAction();
}

void FUnrealCharpToolBar::Initialize()
{

	
#if ENGINE_MAJOR_VERSION >= 5

	// 注册到菜单选项中
	UToolMenu* ToolbarMenu    = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	FToolMenuSection& Section = ToolbarMenu->AddSection("CSharpEditor");
	Section.AddEntry(FToolMenuEntry::InitComboButton(
		"CSharpEditor",
		FUIAction(),
		FOnGetContent::CreateRaw(this, &FUnrealCharpToolBar::GenerateToolBarMenu),
		LOCTEXT("CSharpEditor_Label", "CSharpEditor"),
		LOCTEXT("CSharpEditor_ToolTip", "CSharpEditor"),
		FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction")
		));
#else
	TSharedPtr<FExtender> Extender = MakeShareable(new FExtender);
	Extender->AddToolBarExtension("Settings", EExtensionHook::After, CommandList,
								  FToolBarExtensionDelegate::CreateLambda([this](FToolBarBuilder& Builder)
								  {
									  Builder.BeginSection(NAME_None);
									  Builder.AddComboButton(FUIAction(),
															 FOnGetContent::CreateRaw(this, &FUnrealCharpToolBar::GenerateGameTableSettingsMenu),
															 LOCTEXT("CSharpEditor_Label", "CSharpEditor"),
															 LOCTEXT("CSharpEditor_ToolTip", "CSharpEditor"),
															 FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction")
									  );
									  Builder.EndSection();
								  })
	);
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(Extender);
#endif
}

void FUnrealCharpToolBar::BuildAction()
{
	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().PluginAction,
		FExecuteAction::CreateLambda([]
		{
			const FUnrealCSharpEditorModule* CSharpEditorModule = 
	FModuleManager::GetModulePtr<FUnrealCSharpEditorModule>("UnrealCSharpEditor");
			if ( CSharpEditorModule != nullptr )
			{
				CSharpEditorModule->PluginButtonClicked();
			}
		}),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FUnrealCSharpEditorCommands::Get().OpenEditorSettings,
		FExecuteAction::CreateLambda([]
		{
			if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings") )
			{
				SettingsModule->ShowViewer("Project", "Plugins", "UnrealCSharpEditorSettings");
			}
		}), FCanExecuteAction());
}

TSharedRef<SWidget> FUnrealCharpToolBar::GenerateToolBarMenu()
{
	const FUnrealCSharpEditorCommands& Commands = FUnrealCSharpEditorCommands::Get();
	FMenuBuilder MenuBuilder(true, PluginCommands);

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("Section_Action", "Action"));
	MenuBuilder.AddMenuEntry(Commands.PluginAction, NAME_None,
								 LOCTEXT("GeneratorCode", "Generator Code"));
	MenuBuilder.EndSection();

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("Section_Help", "Help"));
	MenuBuilder.AddMenuEntry(Commands.OpenEditorSettings, NAME_None,
	                         LOCTEXT("OpenEditorSettings", "Open Settings"));
	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}


#undef LOCTEXT_NAMESPACE
