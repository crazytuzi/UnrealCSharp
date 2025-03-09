#include "NewClass/SDynamicClassViewer.h"
#include "Misc/TextFilterExpressionEvaluator.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SSearchBox.h"
#include "NewClass/ClassCollector.h"

TSharedPtr<FClassCollector> SDynamicClassViewer::ClassCollector;

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDynamicClassViewer::Construct(const FArguments& InArgs)
{
	OnDynamicClassNodePickedDelegate = InArgs._OnDynamicClassNodePicked;

	OnDynamicClassNodeDoubleClickedDelegate = InArgs._OnDynamicClassNodeDoubleClicked;

	if (!ClassCollector.IsValid())
	{
		ClassCollector = MakeShared<FClassCollector>();
	}

	AllItems = ClassCollector->GetAllNodes();

	TextFilter = MakeShared<FTextFilterExpressionEvaluator>(ETextFilterExpressionEvaluatorMode::BasicString);

	AllItems.Sort([](const TSharedPtr<FDynamicClassViewerNode>& A, const TSharedPtr<FDynamicClassViewerNode>& B)
	{
		return A->AssetClassName.Compare(B->AssetClassName, ESearchCase::IgnoreCase) < 0;
	});

	FilteredItems = AllItems;

	SearchText = FText::GetEmpty();

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(2)
		[
			SAssignNew(SearchBox, SSearchBox)
			.OnTextChanged(this, &SDynamicClassViewer::OnSearchTextChanged)
			.OnTextCommitted(this, &SDynamicClassViewer::OnSearchTextCommitted)
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SAssignNew(ListView, SListView<TSharedPtr<FDynamicClassViewerNode>>)
			.ListItemsSource(&FilteredItems)
			.SelectionMode(ESelectionMode::Single)
			.OnGenerateRow(this, &SDynamicClassViewer::OnGenerateRow)
			.OnSelectionChanged(this, &SDynamicClassViewer::OnSelectionChanged)
			.OnMouseButtonDoubleClick(this, &SDynamicClassViewer::OnNodeDoubleClicked)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		.HAlign(HAlign_Left)
		[
			SNew(STextBlock)
			.Text(this, &SDynamicClassViewer::GetItemCountText)
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

bool SDynamicClassViewer::ValidateClass(const FString& InClassName) const
{
	return !ClassCollector.IsValid() ? false : ClassCollector->ValidateNode(InClassName);
}

TSharedRef<ITableRow> SDynamicClassViewer::OnGenerateRow(
	TSharedPtr<FDynamicClassViewerNode> Item,
	const TSharedRef<STableViewBase>& OwnerTable) const
{
	auto FontInfo = FAppStyle::Get().GetFontStyle("PropertyWindow.NormalFont");

	FontInfo.Size = 10;

	return SNew(STableRow<TSharedPtr<FDynamicClassViewerNode>>, OwnerTable)
		.Padding(FMargin(2.0f))
		.ShowSelection(true)
		.SignalSelectionMode(ETableRowSignalSelectionMode::Instantaneous)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			.Padding(5.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Item->AssetClassName))
				.HighlightText(SearchText)
				.Font(FontInfo)
				.ColorAndOpacity(FLinearColor(0.9f, 0.9f, 0.9f, 1.0f))
			]
		];
}

void SDynamicClassViewer::OnSelectionChanged(TSharedPtr<FDynamicClassViewerNode> Item,
                                             ESelectInfo::Type SelectType)
{
	if (!Item.IsValid() || !OnDynamicClassNodePickedDelegate.IsBound())
	{
		return;
	}

	if (ListView.IsValid())
	{
		FSlateApplication::Get().SetKeyboardFocus(ListView.ToSharedRef());
	}

	OnDynamicClassNodePickedDelegate.Execute(Item);
}

void SDynamicClassViewer::OnNodeDoubleClicked(TSharedPtr<FDynamicClassViewerNode> Item)
{
	if (!Item.IsValid() || !OnDynamicClassNodeDoubleClickedDelegate.IsBound())
	{
		return;
	}

	OnDynamicClassNodeDoubleClickedDelegate.Execute(Item);
}

void SDynamicClassViewer::OnSearchTextChanged(const FText& InSearchText)
{
	if (!ListView.IsValid())
	{
		return;
	}

	SearchText = InSearchText;

	TextFilter->SetFilterText(InSearchText);

	UpdateFilteredItems();

	ListView->RequestListRefresh();
}

void SDynamicClassViewer::OnSearchTextCommitted(const FText& InSearchText, ETextCommit::Type CommitType)
{
	if (!ListView.IsValid())
	{
		return;
	}

	SearchText = InSearchText;

	UpdateFilteredItems();

	FSlateApplication::Get().SetKeyboardFocus(ListView.ToSharedRef());
}

void SDynamicClassViewer::UpdateFilteredItems()
{
	const auto SearchString = SearchText.ToString();

	FilteredItems.Empty();

	if (SearchString.IsEmpty())
	{
		FilteredItems = AllItems;
	}
	else
	{
		for (const auto& Item : AllItems)
		{
			if (TextFilter->TestTextFilter(FBasicStringFilterExpressionContext(Item->AssetClassName)))
			{
				FilteredItems.Add(Item);
			}
		}
	}

	FilteredItems.Sort([](const TSharedPtr<FDynamicClassViewerNode>& A, const TSharedPtr<FDynamicClassViewerNode>& B)
	{
		return A->AssetClassName.Compare(B->AssetClassName, ESearchCase::IgnoreCase) < 0;
	});

	if (ListView.IsValid())
	{
		ListView->RebuildList();
	}
}

FText SDynamicClassViewer::GetItemCountText() const
{
	return FText::Format(NSLOCTEXT("ClassViewer", "ItemCount", "Items Count: {0}"),
	                     FText::AsNumber(FilteredItems.Num()));
}
