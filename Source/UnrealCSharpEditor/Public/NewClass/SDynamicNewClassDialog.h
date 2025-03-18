#pragma once

#include "CoreMinimal.h"

struct FProjectContent;
class IClassViewerFilter;
class SEditableTextBox;
class SWizard;
class SDynamicClassViewer;
struct FDynamicNewClassInfo;
struct FDynamicClassViewerNode;

class SDynamicNewClassDialog final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDynamicNewClassDialog)
		{
		}

		SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow)

		SLATE_ARGUMENT(FString, InitialPath)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	TSharedRef<ITableRow> MakeParentClassListViewWidget(TSharedPtr<FDynamicNewClassInfo> ParentClassItem,
	                                                    const TSharedRef<STableViewBase>& OwnerTable);

	FText GetSelectedParentClassName() const;

	void OnCommonClassItemSelected(TSharedPtr<FDynamicNewClassInfo> Item, ESelectInfo::Type SelectInfo);

	void OnCommonClassItemDoubleClicked(TSharedPtr<FDynamicNewClassInfo> Item);

	void OnAllClassItemSelected(TSharedPtr<FDynamicClassViewerNode> Item);

	void OnAllClassItemDoubleClicked(TSharedPtr<FDynamicClassViewerNode> Item);

	void MainWizardShowNextPage() const;

	bool IsShowFullClassTree() const;

	void OnAllClassVisibilityChanged(bool bInShowFullClassTree);

	EVisibility GetCommonClassVisibility() const;

	EVisibility GetAllClassVisibility() const;

	EVisibility GetNameErrorLabelVisibility() const;

	void OnNewClassTypeChanged(const int32 NewTypeIndex);

	FText GetNameErrorLabelText() const;

	void OnNamePageEntered();

	FText GetNameClassTitle() const;

	FText OnGetClassNameText() const;

	void OnClassNameTextChanged(const FText& NewText);

	void OnClassNameTextCommitted(const FText& NewText, ETextCommit::Type CommitType);

	FText OnGetClassPathText() const;

	void OnClassPathTextChanged(const FText& NewText);

	FText OnGetParentClassNameText() const;

	FText OnGetDynamicFilePathText() const;

	FString GetDynamicFileName() const;

	void CancelClicked();

	bool CanFinish() const;

	void FinishClicked();

	FReply HandleChooseFolderButtonClicked();

	FText GetSelectedProjectComboText() const;

	void SelectedProjectComboBoxSelectionChanged(TSharedPtr<FProjectContent> Value, ESelectInfo::Type SelectInfo);

	TSharedRef<SWidget> MakeWidgetForSelectedModuleCombo(TSharedPtr<FProjectContent> Value);

private:
	void UpdateInputValidity();

	void SetupDefaultCommonParentClassItems();

	void CloseContainingWindow();

private:
	TSharedPtr<SWizard> MainWizard;

	TSharedPtr<SListView<TSharedPtr<FDynamicNewClassInfo>>> ParentClassListView;

	TArray<TSharedPtr<FDynamicNewClassInfo>> ParentClassItemsSource;

	TSharedPtr<SDynamicClassViewer> DynamicClassViewer;

	int32 NewClassTypeIndex{};

	TSharedPtr<SEditableTextBox> ClassNameEditBox;

	TSharedPtr<SComboBox<TSharedPtr<FProjectContent>>> AvailableProjectsComboBox;

	FString NewClassName;

	FString NewClassPath;

	TSharedPtr<FDynamicClassViewerNode> SelectedParentClassInfo;

	bool bShowFullClassTree{};

	double LastPeriodicValidityCheckTime{};

	double PeriodicValidityCheckFrequency{};

	bool bPreventPeriodicValidityChecksUntilNextChange{};

	FText LastInputValidityErrorText;

	bool bLastInputValidityCheckSuccessful{};

	TArray<TSharedPtr<FProjectContent>> AvailableProjects;

	TSharedPtr<FProjectContent> SelectedProjectContent;
};
