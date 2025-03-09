#pragma once

#include "CoreMinimal.h"
#include "UEVersion.h"
#include "NewClass/DynamicNewClassUtils.h"

struct FDynamicClassViewerNode
{
	FString AssetClassName;

	FString ObjectPath;

	explicit FDynamicClassViewerNode(const FString& InAssetName, const FString& InObjectPath):
		AssetClassName(InAssetName),
		ObjectPath(InObjectPath)
	{
	}

	explicit FDynamicClassViewerNode(const FAssetData& InAssetData)
	{
		AssetClassName = FDynamicNewClassUtils::GetAssetGeneratedClassName(InAssetData);

#if UE_ASSET_DATA_GET_OBJECT_PATH_STRING
		ObjectPath = InAssetData.GetObjectPathString();
#else
		ObjectPath = InAssetData.ObjectPath.ToString();
#endif
	}

	UClass* GetClass() const
	{
		if (AssetClassName.Equals(TEXT("None")))
		{
			return nullptr;
		}

		if (const auto Class = LoadObject<UClass>(nullptr, *ObjectPath))
		{
			return Class;
		}

		if (const auto Blueprint = LoadObject<UBlueprint>(nullptr, *ObjectPath))
		{
			if (Blueprint->GeneratedClass != nullptr)
			{
				return Cast<UClass>(Blueprint->GeneratedClass);
			}
		}

		return nullptr;
	}

	bool operator==(const FDynamicClassViewerNode& Other) const
	{
		return AssetClassName == Other.AssetClassName;
	}
};

class SDynamicClassViewer final : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnDynamicClassNodePicked, TSharedPtr<FDynamicClassViewerNode>);

	DECLARE_DELEGATE_OneParam(FOnDynamicClassNodeDoubleClicked, TSharedPtr<FDynamicClassViewerNode>);

public:
	SLATE_BEGIN_ARGS(SDynamicClassViewer)
		{
		}

		SLATE_EVENT(FOnDynamicClassNodePicked, OnDynamicClassNodePicked)

		SLATE_EVENT(FOnDynamicClassNodeDoubleClicked, OnDynamicClassNodeDoubleClicked)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	bool ValidateClass(const FString& InClassName) const;

private:
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDynamicClassViewerNode> Item,
	                                    const TSharedRef<STableViewBase>& OwnerTable) const;

	void OnSelectionChanged(TSharedPtr<FDynamicClassViewerNode> Item, ESelectInfo::Type SelectType);

	void OnNodeDoubleClicked(TSharedPtr<FDynamicClassViewerNode> Item);

	void OnSearchTextChanged(const FText& InSearchText);

	void OnSearchTextCommitted(const FText& InSearchText, ETextCommit::Type CommitType);

	void UpdateFilteredItems();

	FText GetItemCountText() const;

private:
	TSharedPtr<SSearchBox> SearchBox;

	TSharedPtr<SListView<TSharedPtr<FDynamicClassViewerNode>>> ListView;

	static TSharedPtr<class FClassCollector> ClassCollector;

	TSharedPtr<class FTextFilterExpressionEvaluator> TextFilter;

	TArray<TSharedPtr<FDynamicClassViewerNode>> AllItems;

	TArray<TSharedPtr<FDynamicClassViewerNode>> FilteredItems;

	FText SearchText;

	FOnDynamicClassNodePicked OnDynamicClassNodePickedDelegate;

	FOnDynamicClassNodeDoubleClicked OnDynamicClassNodeDoubleClickedDelegate;
};
