#include "NewClass/SDynamicNewClassDialog.h"
#include "DesktopPlatformModule.h"
#include "SourceCodeNavigation.h"
#include "IDocumentation.h"
#include "EditorClassUtils.h"
#include "SlateOptMacros.h"
#include "Widgets/Workflow/SWizard.h"
#include "Widgets/Input/SSegmentedControl.h"
#include "Widgets/Layout/SGridPanel.h"
#include "SWarningOrErrorBox.h"
#include "TutorialMetaData.h"
#include "AddToProjectConfig.h"
#include "FeaturedClasses.inl"
#include "ClassIconFinder.h"
#include "GameProjectUtils.h"
#include "NewClass/SDynamicClassViewer.h"
#include "NewClass/DynamicNewClassInfo.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "UEVersion.h"

#define LOCTEXT_NAMESPACE "DynamicNewClassDialog"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDynamicNewClassDialog::Construct(const FArguments& InArgs)
{
	const auto& ProjectContent = FDynamicNewClassUtils::GetProjectContent();

	AvailableProjects.Reserve(ProjectContent.Num());

	for (const auto& Project : ProjectContent)
	{
		AvailableProjects.Emplace(MakeShared<FProjectContent>(Project));
	}

	if (AvailableProjects.IsEmpty())
	{
		return;
	}

	const auto AbsoluteInitialPath = InArgs._InitialPath.IsEmpty()
		                                 ? FUnrealCSharpFunctionLibrary::GetGameDirectory()
		                                 : InArgs._InitialPath;

	NewClassPath = AbsoluteInitialPath;

	for (const auto& AvailableProject : AvailableProjects)
	{
		if (AbsoluteInitialPath.StartsWith(AvailableProject->SourcePath))
		{
			SelectedProjectContent = AvailableProject;

			break;
		}
	}

	if (!SelectedProjectContent.IsValid())
	{
		SelectedProjectContent = AvailableProjects.Top();
	}

	NewClassTypeIndex = 0;

	bShowFullClassTree = false;

	LastPeriodicValidityCheckTime = 0;

	PeriodicValidityCheckFrequency = 4;

	bLastInputValidityCheckSuccessful = true;

	bPreventPeriodicValidityChecksUntilNextChange = false;

	DynamicClassViewer = SNew(SDynamicClassViewer)
		.OnDynamicClassNodePicked(this, &SDynamicNewClassDialog::OnAllClassItemSelected)
		.OnDynamicClassNodeDoubleClicked(this, &SDynamicNewClassDialog::OnAllClassItemDoubleClicked);

	SetupDefaultCommonParentClassItems();

	UpdateInputValidity();

	constexpr auto EditableTextHeight = 26.0f;

	ChildSlot
	[
		SNew(SBorder)
		.Padding(18)
		.BorderImage(
#if UE_APP_STYLE_GET_BRUSH
			FAppStyle::GetBrush("Docking.Tab.ContentAreaBrush"))
#else
			FEditorStyle::GetBrush("Docking.Tab.ContentAreaBrush"))
#endif
		[
			SNew(SVerticalBox)
			.AddMetaData<FTutorialMetaData>(TEXT("AddCodeMajorAnchor"))
			+ SVerticalBox::Slot()
			[
				SAssignNew(MainWizard, SWizard)
				.ShowPageList(false)
				.CanFinish(this, &SDynamicNewClassDialog::CanFinish)
				.FinishButtonText(LOCTEXT("FinishButtonText_Dynamic", "Create Dynamic Class"))
				.FinishButtonToolTip(
					LOCTEXT("FinishButtonToolTip_Dynamic", "Creates the code files to add your new dynamic class."))
				.OnCanceled(this, &SDynamicNewClassDialog::CancelClicked)
				.OnFinished(this, &SDynamicNewClassDialog::FinishClicked)
				.InitialPageIndex(0)
				+ SWizard::Page()
				.CanShow(true)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0)
					[
						SNew(STextBlock)
						.Font(FAppStyle::Get().GetFontStyle("HeadingExtraSmall"))
						.Text(LOCTEXT("ParentClassTitle", "Choose Parent Class"))
						.TransformPolicy(ETextTransformPolicy::ToUpper)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Center)
					[
						SNew(SSegmentedControl<bool>)
						.Value(this, &SDynamicNewClassDialog::IsShowFullClassTree)
						.OnValueChanged(this, &SDynamicNewClassDialog::OnAllClassVisibilityChanged)
						+ SSegmentedControl<bool>::Slot(false)
						.Text(LOCTEXT("CommonClasses", "Common Classes"))
						+ SSegmentedControl<bool>::Slot(true)
						.Text(LOCTEXT("AllClasses", "All Classes"))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0, 10)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("ChooseParentClassDescription_Dynamic",
						              "This will add a dynamic class file to your game project."))
					]
					+ SVerticalBox::Slot()
					.FillHeight(1.f)
					.Padding(0, 10)
					[
						SNew(SBorder)
						.AddMetaData<FTutorialMetaData>(TEXT("AddCodeOptions"))
						.BorderImage(
#if UE_APP_STYLE_GET_BRUSH
							FAppStyle::GetBrush("ToolPanel.GroupBorder"))
#else
							FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
#endif
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							[
								SAssignNew(ParentClassListView, SListView< TSharedPtr<FDynamicNewClassInfo> >)
								.ListItemsSource(&ParentClassItemsSource)
								.SelectionMode(ESelectionMode::Single)
								.ClearSelectionOnClick(false)
								.OnGenerateRow(this, &SDynamicNewClassDialog::MakeParentClassListViewWidget)
								.OnMouseButtonDoubleClick(this, &SDynamicNewClassDialog::OnCommonClassItemDoubleClicked)
								.OnSelectionChanged(this, &SDynamicNewClassDialog::OnCommonClassItemSelected)
								.Visibility(this, &SDynamicNewClassDialog::GetCommonClassVisibility)
							]
							+ SVerticalBox::Slot()
							[
								SNew(SBox)
								.Visibility(this, &SDynamicNewClassDialog::GetAllClassVisibility)
								[
									DynamicClassViewer.ToSharedRef()
								]
							]
						]
					]
					+ SVerticalBox::Slot()
					.Padding(30, 2)
					.AutoHeight()
					[
						SNew(SGridPanel)
						.FillColumn(1, 1.0f)
						+ SGridPanel::Slot(0, 0)
						.VAlign(VAlign_Center)
						.Padding(2.0f, 2.0f, 10.0f, 2.0f)
						.HAlign(HAlign_Left)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ParentClassLabel", "Selected Class"))
						]
						+ SGridPanel::Slot(1, 0)
						.VAlign(VAlign_Center)
						.Padding(2.0f)
						.HAlign(HAlign_Left)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.VAlign(VAlign_Center)
							.AutoWidth()
							[
								SNew(STextBlock)
								.Text(this, &SDynamicNewClassDialog::GetSelectedParentClassName)
							]
						]
					]
				]
				+ SWizard::Page()
				.OnEnter(this, &SDynamicNewClassDialog::OnNamePageEntered)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0)
					[
						SNew(STextBlock)
						.Font(FAppStyle::Get().GetFontStyle("HeadingExtraSmall"))
						.Text(this, &SDynamicNewClassDialog::GetNameClassTitle)
						.TransformPolicy(ETextTransformPolicy::ToUpper)
					]
					+ SVerticalBox::Slot()
					.FillHeight(1.f)
					.Padding(0, 10)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 0, 0, 5)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ClassNameDescription",
							              "Enter a name for your new class. Class names may only contain alphanumeric characters, and may not contain a space."))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 0, 0, 2)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("ClassNameDetails_Blueprint",
							              "When you click the \"Create\" button below, a new dynamic class will be created."))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(0, 5)
						[
							SNew(SWarningOrErrorBox)
							.MessageStyle(EMessageStyle::Error)
							.Visibility(this, &SDynamicNewClassDialog::GetNameErrorLabelVisibility)
							.Message(this, &SDynamicNewClassDialog::GetNameErrorLabelText)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder)
							.BorderImage(
#if UE_APP_STYLE_GET_BRUSH
								FAppStyle::GetBrush("DetailsView.CategoryTop"))
#else
								FEditorStyle::GetBrush("DetailsView.CategoryTop"))
#endif
							.BorderBackgroundColor(FLinearColor(0.6f, 0.6f, 0.6f, 1.0f))
							.Padding(FMargin(6.0f, 4.0f, 7.0f, 4.0f))
							[
								SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								.Padding(0)
								[
									SNew(SGridPanel)
									.FillColumn(1, 1.0f)
									+ SGridPanel::Slot(0, 0)
									.VAlign(VAlign_Center)
									.Padding(0, 0, 12, 0)
									[
										SNew(STextBlock)
										.Text(LOCTEXT("NewClassType_Label", "Dynamic Class Type"))
									]
									+ SGridPanel::Slot(1, 0)
									.VAlign(VAlign_Center)
									.HAlign(HAlign_Left)
									.Padding(2.0f)
									[
										SNew(SSegmentedControl<int32>)
										.Value_Lambda([this] { return NewClassTypeIndex; })
										.OnValueChanged(this, &SDynamicNewClassDialog::OnNewClassTypeChanged)
										.IsEnabled_Lambda([this]
										{
											return !SelectedParentClassInfo.IsValid()
												       ? true
												       : !SelectedParentClassInfo->AssetClassName.EndsWith(TEXT("_C"));
										})
										+ SSegmentedControl<int32>::Slot(0)
										.Text(LOCTEXT("NewClassType_Cpp", "C++"))
										+ SSegmentedControl<int32>::Slot(1)
										.Text(LOCTEXT("NewClassType_BP", "Blueprint"))
									]
									+ SGridPanel::Slot(1, 0)
									.VAlign(VAlign_Center)
									.HAlign(HAlign_Left)
									.Padding(2.0f)
									+ SGridPanel::Slot(0, 1)
									.VAlign(VAlign_Center)
									.Padding(0, 0, 12, 0)
									[
										SNew(STextBlock)
										.Text(LOCTEXT("NameLabel", "Name"))
									]
									+ SGridPanel::Slot(1, 1)
									.Padding(0.0f, 3.0f)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.HeightOverride(EditableTextHeight)
										.AddMetaData<FTutorialMetaData>(TEXT("ClassName"))
										[
											SNew(SHorizontalBox)
											+ SHorizontalBox::Slot()
											.FillWidth(.7f)
											[
												SAssignNew(ClassNameEditBox, SEditableTextBox)
												.Text(this, &SDynamicNewClassDialog::OnGetClassNameText)
												.OnTextChanged(this, &SDynamicNewClassDialog::OnClassNameTextChanged)
												.OnTextCommitted(
													this, &SDynamicNewClassDialog::OnClassNameTextCommitted)
											]
											+ SHorizontalBox::Slot()
											.AutoWidth()
											.Padding(6.0f, 0.0f, 0.0f, 0.0f)
											[
												SAssignNew(AvailableProjectsComboBox,
												           SComboBox<TSharedPtr<FProjectContent>>)
												.Visibility(EVisibility::Visible)
												.ToolTipText(LOCTEXT("ProjectComboToolTip",
												                     "Choose the target project for your new class"))
												.OptionsSource(&AvailableProjects)
												.InitiallySelectedItem(SelectedProjectContent)
												.OnSelectionChanged(
													this,
													&SDynamicNewClassDialog::SelectedProjectComboBoxSelectionChanged)
												.OnGenerateWidget(
													this, &SDynamicNewClassDialog::MakeWidgetForSelectedModuleCombo)
												[
													SNew(STextBlock)
													.Text(this, &SDynamicNewClassDialog::GetSelectedProjectComboText)
												]
											]
										]
									]
									+ SGridPanel::Slot(0, 2)
									.VAlign(VAlign_Center)
									.Padding(0, 0, 12, 0)
									[
										SNew(STextBlock)
										.Text(LOCTEXT("PathLabel", "Path"))
									]
									+ SGridPanel::Slot(1, 2)
									.Padding(0.0f, 3.0f)
									.VAlign(VAlign_Center)
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
										.Padding(0)
										.AutoHeight()
										[
											SNew(SBox)
											.Visibility(EVisibility::Visible)
											.HeightOverride(EditableTextHeight)
											.AddMetaData<FTutorialMetaData>(TEXT("Path"))
											[
												SNew(SHorizontalBox)
												+ SHorizontalBox::Slot()
												.FillWidth(1.0f)
												[
													SNew(SEditableTextBox)
													.Text(this, &SDynamicNewClassDialog::OnGetClassPathText)
													.OnTextChanged(
														this, &SDynamicNewClassDialog::OnClassPathTextChanged)
												]
												+ SHorizontalBox::Slot()
												.AutoWidth()
												.Padding(6.0f, 1.0f, 0.0f, 0.0f)
												[
													SNew(SButton)
													.VAlign(VAlign_Center)
													.ButtonStyle(FAppStyle::Get(), "SimpleButton")
													.OnClicked(
														this, &SDynamicNewClassDialog::HandleChooseFolderButtonClicked)
													[
														SNew(SImage)
														.Image(FAppStyle::Get().GetBrush("Icons.FolderClosed"))
														.ColorAndOpacity(FSlateColor::UseForeground())
													]
												]
											]
										]
									]
									+ SGridPanel::Slot(0, 3)
									.VAlign(VAlign_Center)
									.Padding(0, 0, 12, 0)
									[
										SNew(STextBlock)
										.Visibility(EVisibility::Visible)
										.Text(LOCTEXT("ParentClassNameLabel", "Parent Class"))
									]
									+ SGridPanel::Slot(1, 3)
									.Padding(0.0f, 3.0f)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Visibility(EVisibility::Visible)
										.VAlign(VAlign_Center)
										.HeightOverride(EditableTextHeight)
										[
											SNew(STextBlock)
											.Text(this, &SDynamicNewClassDialog::OnGetParentClassNameText)
										]
									]
									+ SGridPanel::Slot(0, 4)
									.VAlign(VAlign_Center)
									.Padding(0, 0, 12, 0)
									[
										SNew(STextBlock)
										.Visibility(EVisibility::Visible)
										.Text(LOCTEXT("HeaderFileLabel", "Dynamic File Path"))
									]
									+ SGridPanel::Slot(1, 4)
									.Padding(0.0f, 3.0f)
									.VAlign(VAlign_Center)
									[
										SNew(SBox)
										.Visibility(EVisibility::Visible)
										.VAlign(VAlign_Center)
										.HeightOverride(EditableTextHeight)
										[
											SNew(STextBlock)
											.Text(this, &SDynamicNewClassDialog::OnGetDynamicFilePathText)
										]
									]
								]
							]
						]
					]
				]
			]
		]
	];

	if (const auto ParentWindow = InArgs._ParentWindow)
	{
		ParentWindow->SetWidgetToFocusOnActivate(ParentClassListView);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedRef<ITableRow> SDynamicNewClassDialog::MakeParentClassListViewWidget(
	TSharedPtr<FDynamicNewClassInfo> ParentClassItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (!ParentClassItem.IsValid() || !ParentClassItem->IsSet())
	{
		return SNew(STableRow<TSharedPtr<FDynamicNewClassInfo>>, OwnerTable);
	}

	const auto ClassName = ParentClassItem->GetClassName();

	const auto ClassFullDescription = ParentClassItem->GetClassDescription(true);

	const auto ClassShortDescription = ParentClassItem->GetClassDescription(false);

	const auto Class = ParentClassItem->BaseClass;

	const auto ClassBrush = FClassIconFinder::FindThumbnailForClass(Class);

	constexpr auto ItemHeight = 64;

	return
			SNew(STableRow<TSharedPtr<FDynamicNewClassInfo>>, OwnerTable)
			.Padding(4)
			.Style(
#if UE_APP_STYLE_GET
				FAppStyle::Get(), "NewClassDialog.ParentClassListView.TableRow")
#else
				FEditorStyle::Get(), "NewClassDialog.ParentClassListView.TableRow")
#endif
			.ToolTip(IDocumentation::Get()->CreateToolTip(ClassFullDescription, nullptr,
			                                              FEditorClassUtils::GetDocumentationPage(Class),
			                                              FEditorClassUtils::GetDocumentationExcerpt(Class)))
			[
				SNew(SBox)
				.HeightOverride(ItemHeight)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.HAlign(HAlign_Center)
					.Padding(8)
					[
						SNew(SBox)
						.HeightOverride(ItemHeight / 2.0f)
						.WidthOverride(ItemHeight / 2.0f)
						[
							SNew(SImage)
							.Image(ClassBrush)
						]
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					.Padding(4)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(STextBlock)
							.TextStyle(FAppStyle::Get(), "DialogButtonText")
							.Text(ClassName)
						]

						+ SVerticalBox::Slot()
						[
							SNew(STextBlock)
							.Text(ClassShortDescription)
							.AutoWrapText(true)
						]
					]
				]
			];
}

FText SDynamicNewClassDialog::GetSelectedParentClassName() const
{
	return FText::FromString(SelectedParentClassInfo.IsValid()
		                         ? SelectedParentClassInfo->AssetClassName
		                         : TEXT("None"));
}

void SDynamicNewClassDialog::OnCommonClassItemSelected(TSharedPtr<FDynamicNewClassInfo> Item,
                                                       ESelectInfo::Type SelectInfo)
{
	if (!Item.IsValid() || Item->BaseClass == nullptr)
	{
		return;
	}

	SelectedParentClassInfo = MakeShared<FDynamicClassViewerNode>(
		Item->GetClassNameCPP(), Item->BaseClass->GetPathName());

	UpdateInputValidity();
}

void SDynamicNewClassDialog::OnCommonClassItemDoubleClicked(TSharedPtr<FDynamicNewClassInfo> Item)
{
	if (!Item.IsValid() || !Item->IsSet())
	{
		return;
	}

	MainWizardShowNextPage();
}

void SDynamicNewClassDialog::OnAllClassItemSelected(TSharedPtr<FDynamicClassViewerNode> Item)
{
	if (!Item.IsValid())
	{
		return;
	}

	const auto ParentClass = Item->GetClass();

	if (ParentClass == nullptr)
	{
		return;
	}

	SelectedParentClassInfo = MakeShared<FDynamicClassViewerNode>(ParentClass->GetName(), Item->ObjectPath);

	UpdateInputValidity();
}

void SDynamicNewClassDialog::OnAllClassItemDoubleClicked(TSharedPtr<FDynamicClassViewerNode> Item)
{
	if (!Item.IsValid() || Item->GetClass() == nullptr)
	{
		return;
	}

	MainWizardShowNextPage();
}

void SDynamicNewClassDialog::MainWizardShowNextPage() const
{
	if (constexpr auto NamePageIdx = 1; MainWizard->CanShowPage(NamePageIdx))
	{
		MainWizard->ShowPage(NamePageIdx);
	}
}

bool SDynamicNewClassDialog::IsShowFullClassTree() const
{
	return bShowFullClassTree;
}

void SDynamicNewClassDialog::OnAllClassVisibilityChanged(const bool bInShowFullClassTree)
{
	bShowFullClassTree = bInShowFullClassTree;
}

EVisibility SDynamicNewClassDialog::GetCommonClassVisibility() const
{
	return bShowFullClassTree ? EVisibility::Collapsed : EVisibility::Visible;
}

EVisibility SDynamicNewClassDialog::GetAllClassVisibility() const
{
	return bShowFullClassTree ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility SDynamicNewClassDialog::GetNameErrorLabelVisibility() const
{
	return GetNameErrorLabelText().IsEmpty() ? EVisibility::Hidden : EVisibility::Visible;
}

void SDynamicNewClassDialog::OnNewClassTypeChanged(const int32 NewTypeIndex)
{
	NewClassTypeIndex = NewTypeIndex;

	if (NewClassTypeIndex == 1 && !NewClassName.EndsWith(TEXT("_C")))
	{
		NewClassName += TEXT("_C");
	}

	if (NewClassTypeIndex == 0)
	{
		NewClassName.RemoveFromEnd(TEXT("_C"));
	}

	UpdateInputValidity();
}

FText SDynamicNewClassDialog::GetNameErrorLabelText() const
{
	return !bLastInputValidityCheckSuccessful ? LastInputValidityErrorText : FText::GetEmpty();
}

void SDynamicNewClassDialog::OnNamePageEntered()
{
	if (!SelectedParentClassInfo.IsValid())
	{
		return;
	}

	const auto ParentClassName = SelectedParentClassInfo->AssetClassName;

	NewClassTypeIndex = ParentClassName.EndsWith(
		                    TEXT("_C"))
		                    ? 1
		                    : 0;

	const auto PotentialNewClassName = FString::Printf(TEXT(
		"%s%s%s"
	),
	                                                   *DYNAMIC_CLASS_DEFAULT_PREFIX,
	                                                   ParentClassName.IsEmpty()
		                                                   ? TEXT("Class")
		                                                   : *ParentClassName,
	                                                   NewClassTypeIndex == 1
		                                                   ? ParentClassName.EndsWith(TEXT("_C"))
			                                                     ? TEXT("")
			                                                     : TEXT("_C")
		                                                   : TEXT("")
	);

	NewClassName = PotentialNewClassName;

	UpdateInputValidity();

	FSlateApplication::Get().SetKeyboardFocus(ClassNameEditBox, EFocusCause::SetDirectly);
}

FText SDynamicNewClassDialog::GetNameClassTitle() const
{
	if (const auto ParentClassName = GetSelectedParentClassName();
		!ParentClassName.IsEmpty() && ParentClassName.ToString() != TEXT("None"))
	{
		return FText::Format(LOCTEXT("NameClassTitle", "Name Your New {0}"), ParentClassName);
	}

	return LOCTEXT("NameClassGenericTitle", "Name Your New Class");
}

FText SDynamicNewClassDialog::OnGetClassNameText() const
{
	return FText::FromString(NewClassName);
}

void SDynamicNewClassDialog::OnClassNameTextChanged(const FText& NewText)
{
	NewClassName = NewText.ToString();

	UpdateInputValidity();
}

void SDynamicNewClassDialog::OnClassNameTextCommitted(const FText& NewText, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::OnEnter)
	{
		if (CanFinish())
		{
			FinishClicked();
		}
	}
}

FText SDynamicNewClassDialog::OnGetClassPathText() const
{
	return FText::FromString(NewClassPath);
}

void SDynamicNewClassDialog::OnClassPathTextChanged(const FText& NewText)
{
	NewClassPath = NewText.ToString();

	for (const auto& AvailableProject : AvailableProjects)
	{
		if (NewClassPath.StartsWith(AvailableProject->SourcePath))
		{
			SelectedProjectContent = AvailableProject;

			AvailableProjectsComboBox->SetSelectedItem(SelectedProjectContent);

			break;
		}
	}

	UpdateInputValidity();
}

FText SDynamicNewClassDialog::OnGetParentClassNameText() const
{
	return FText::FromString(
		SelectedParentClassInfo.IsValid() ? SelectedParentClassInfo->AssetClassName : TEXT("Class"));
}

FText SDynamicNewClassDialog::OnGetDynamicFilePathText() const
{
	return FText::FromString(GetDynamicFileName());
}

FString SDynamicNewClassDialog::GetDynamicFileName() const
{
	return NewClassPath / NewClassName + CSHARP_SUFFIX;
}

void SDynamicNewClassDialog::CancelClicked()
{
	CloseContainingWindow();
}

bool SDynamicNewClassDialog::CanFinish() const
{
	return bLastInputValidityCheckSuccessful;
}

void SDynamicNewClassDialog::FinishClicked()
{
	UpdateInputValidity();

	if (CanFinish())
	{
		if (const auto ParentClass = SelectedParentClassInfo->GetClass())
		{
			FString NewClassContent;

			FDynamicNewClassUtils::GetDynamicClassContent(ParentClass, NewClassName, NewClassContent);

			FUnrealCSharpFunctionLibrary::SaveStringToFile(*GetDynamicFileName(), NewClassContent);

			CloseContainingWindow();

			FSourceCodeNavigation::OpenSourceFile(GetDynamicFileName());
		}
	}
}

FReply SDynamicNewClassDialog::HandleChooseFolderButtonClicked()
{
	if (const auto DesktopPlatform = FDesktopPlatformModule::Get())
	{
		const auto ParentWindow = FSlateApplication::Get().FindWidgetWindow(AsShared());

		const auto ParentWindowWindowHandle = ParentWindow.IsValid()
			                                      ? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
			                                      : nullptr;

		FString FolderName;

		const auto Title = LOCTEXT("NewClassBrowseTitle", "Choose a dynamic class source location").ToString();

		const auto bFolderSelected = DesktopPlatform->OpenDirectoryDialog(
			ParentWindowWindowHandle,
			Title,
			NewClassPath,
			FolderName
		);

		if (bFolderSelected)
		{
			if (!FolderName.EndsWith(TEXT("/")))
			{
				FolderName += TEXT("/");
			}

			NewClassPath = FolderName;

			for (const auto& AvailableProject : AvailableProjects)
			{
				if (NewClassPath.StartsWith(AvailableProject->SourcePath))
				{
					SelectedProjectContent = AvailableProject;

					AvailableProjectsComboBox->SetSelectedItem(SelectedProjectContent);

					break;
				}
			}

			UpdateInputValidity();
		}
	}

	return FReply::Handled();
}

FText SDynamicNewClassDialog::GetSelectedProjectComboText() const
{
	FFormatNamedArguments Args;

	Args.Add(TEXT("ProjectName"), FText::FromString(SelectedProjectContent->Name));

	return FText::Format(LOCTEXT("ModuleComboEntry", "{ProjectName}"), Args);
}

void SDynamicNewClassDialog::SelectedProjectComboBoxSelectionChanged(TSharedPtr<FProjectContent> Value,
                                                                     ESelectInfo::Type SelectInfo)
{
	SelectedProjectContent = Value;

	NewClassPath = SelectedProjectContent->SourcePath;

	UpdateInputValidity();
}

TSharedRef<SWidget> SDynamicNewClassDialog::MakeWidgetForSelectedModuleCombo(TSharedPtr<FProjectContent> Value)
{
	FFormatNamedArguments Args;

	Args.Add(TEXT("ProjectName"), FText::FromString(Value->Name));

	return SNew(STextBlock)
		.Text(FText::Format(LOCTEXT("ModuleComboEntry", "{ProjectName}"), Args));
}

void SDynamicNewClassDialog::UpdateInputValidity()
{
	bLastInputValidityCheckSuccessful = GameProjectUtils::IsValidClassNameForCreation(
		NewClassName, LastInputValidityErrorText);

	if (bLastInputValidityCheckSuccessful)
	{
		if (!SelectedParentClassInfo.IsValid())
		{
			bLastInputValidityCheckSuccessful = false;

			LastInputValidityErrorText = LOCTEXT("NotSelectedParentClass",
			                                     "Please select a parent class for your new class.");

			return;
		}

		const auto ParentClass = SelectedParentClassInfo->GetClass();

		if (ParentClass == nullptr)
		{
			bLastInputValidityCheckSuccessful = false;

			LastInputValidityErrorText = FText::Format(
				LOCTEXT("InvalidParentClass_NullPtr", "Invalid parent class {0}."),
				FText::FromString(SelectedParentClassInfo->AssetClassName));

			return;
		}

		if (NewClassTypeIndex == 1 && FDynamicClassGenerator::IsDynamicClass(ParentClass))
		{
			bLastInputValidityCheckSuccessful = false;

			LastInputValidityErrorText = LOCTEXT("CreateDynamicBpClassFromDynamicClass",
			                                     "The dynamic blueprint class cannot select dynamic class as parent class");

			return;
		}

		if (DynamicClassViewer->ValidateClass(NewClassName))
		{
			bLastInputValidityCheckSuccessful = false;

			FFormatNamedArguments Args;

			Args.Add(TEXT("NewClassName"), FText::FromString(NewClassName));

			LastInputValidityErrorText = FText::Format(
				LOCTEXT("ValidClassNameError", "The name {NewClassName} is already used by another class."), Args);

			return;
		}

		auto bIsStartWithProjectDirectory = false;

		for (const auto& AvailableProject : AvailableProjects)
		{
			if (NewClassPath.StartsWith(AvailableProject->SourcePath))
			{
				bIsStartWithProjectDirectory = true;
			}
		}

		if (!bIsStartWithProjectDirectory)
		{
			bLastInputValidityCheckSuccessful = false;

			LastInputValidityErrorText = LOCTEXT("SelectedPathNotProjectDirectory",
			                                     "The selected path is not a project or a custom project path.");

			return;
		}

		if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*OnGetDynamicFilePathText().ToString()))
		{
			bLastInputValidityCheckSuccessful = false;

			LastInputValidityErrorText = FText::Format(
				LOCTEXT("DynamicClassAlreadyExists", "An dynamic class called {0} already exists in {1}."),
				FText::FromString(NewClassName), FText::FromString(NewClassPath));

			return;
		}
	}

	LastPeriodicValidityCheckTime = FSlateApplication::Get().GetCurrentTime();

	bPreventPeriodicValidityChecksUntilNextChange = false;
}

void SDynamicNewClassDialog::SetupDefaultCommonParentClassItems()
{
	TArray<FDynamicNewClassInfo> DefaultFeaturedClasses;

	DefaultFeaturedClasses.Add(FDynamicNewClassInfo(FNewClassInfo::EClassType::EmptyCpp));

	DefaultFeaturedClasses.Add(FDynamicNewClassInfo(UActorComponent::StaticClass()));

	DefaultFeaturedClasses.Append(FFeaturedClasses::ActorClasses());

	DefaultFeaturedClasses.Add(FDynamicNewClassInfo(USceneComponent::StaticClass()));

	for (const auto& DefaultFeaturedClass : DefaultFeaturedClasses)
	{
		ParentClassItemsSource.Add(MakeShared<FDynamicNewClassInfo>(DefaultFeaturedClass));
	}
}

void SDynamicNewClassDialog::CloseContainingWindow()
{
	if (const auto ContainingWindow = FSlateApplication::Get().FindWidgetWindow(AsShared()))
	{
		ContainingWindow->RequestDestroyWindow();
	}
}

FReply SDynamicNewClassDialog::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		CancelClicked();

		return FReply::Handled();
	}

	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		OnCommonClassItemDoubleClicked(TSharedPtr<FDynamicNewClassInfo>());

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void SDynamicNewClassDialog::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
                                  const float InDeltaTime)
{
	if (!bPreventPeriodicValidityChecksUntilNextChange &&
		InCurrentTime > LastPeriodicValidityCheckTime + PeriodicValidityCheckFrequency)
	{
		UpdateInputValidity();
	}
}

#undef LOCTEXT_NAMESPACE
