﻿#include "ContentBrowser/DynamicNewClassContextMenu.h"
#include "ToolMenus.h"
#include "UnrealCSharpEditorStyle.h"

#define LOCTEXT_NAMESPACE "ContentBrowserClassDataSource"

void FDynamicNewClassContextMenu::MakeContextMenu(UToolMenu* InMenu, const TArray<FName>& InSelectedClassPaths,
                                                  const FOnOpenNewDynamicClassRequested&
                                                  InOnOpenNewDynamicClassRequested)
{
	if (InSelectedClassPaths.Num() == 0)
	{
		return;
	}

	const FName FirstSelectedPath = InSelectedClassPaths[0];

	const bool bHasSinglePathSelected = InSelectedClassPaths.Num() == 1;

	auto CanExecuteClassActions = [bHasSinglePathSelected]() -> bool
	{
		return bHasSinglePathSelected;
	};

	const FCanExecuteAction CanExecuteClassActionsDelegate =
		FCanExecuteAction::CreateLambda(CanExecuteClassActions);

	if (InOnOpenNewDynamicClassRequested.IsBound())
	{
		const FName ClassCreationPath = FirstSelectedPath;

		FText NewClassToolTip;

		if (bHasSinglePathSelected)
		{
			NewClassToolTip = FText::Format(
				LOCTEXT("NewClassTooltip_CreateIn", "Create a new dynamic class in {0}."),
				FText::FromName(ClassCreationPath));
		}
		else
		{
			NewClassToolTip = LOCTEXT("NewClassTooltip_SelectedInvalidNumberOfPaths",
			                          "Can only create classes when there is a single path selected.");
		}

		auto& Section = InMenu->AddSection("ContentBrowserNewClass",
		                                   LOCTEXT("ClassMenuHeading", "New Dynamic Class"));
		Section.AddMenuEntry(
			"NewClass",
			LOCTEXT("NewClassLabel", "New dynamic Class..."),
			NewClassToolTip,
			FSlateIcon(FUnrealCSharpEditorStyle::GetStyleSetName(), "UnrealCSharpEditor.PluginAction"),
			FUIAction(
				FExecuteAction::CreateStatic(&FDynamicNewClassContextMenu::ExecuteNewClass, ClassCreationPath,
				                             InOnOpenNewDynamicClassRequested),
				CanExecuteClassActionsDelegate
			)
		);
	}
}

void FDynamicNewClassContextMenu::ExecuteNewClass(const FName InPath,
                                                  FOnOpenNewDynamicClassRequested InOnOpenNewDynamicClassRequested)
{
	InOnOpenNewDynamicClassRequested.ExecuteIfBound(InPath);
}

#undef LOCTEXT_NAMESPACE
