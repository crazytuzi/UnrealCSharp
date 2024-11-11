#include "ContentBrowser/DynamicDataSource.h"
#include "CollectionManagerModule.h"
#include "ContentBrowserDataUtils.h"
#include "ContentBrowserItemPath.h"
#include "SourceCodeNavigation.h"
#if UE_F_NAME_PERMISSION_LIST
#include "Misc/NamePermissionList.h"
#endif
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicGenerator.h"

#ifdef UE_INLINE_GENERATED_CPP_BY_NAME
#include UE_INLINE_GENERATED_CPP_BY_NAME(DynamicDataSource)
#endif

#define LOCTEXT_NAMESPACE "UDynamicDataSource"

void UDynamicDataSource::Initialize(const bool InAutoRegister)
{
	Super::Initialize(InAutoRegister);

	OnDynamicClassUpdatedHandle = FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.AddUObject(
		this, &UDynamicDataSource::OnDynamicClassUpdated);

	OnEndGeneratorHandle = FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddUObject(
		this, &UDynamicDataSource::OnEndGenerator);

	CollectionManager = &FCollectionManagerModule::GetModule().Get();

	BuildRootPathVirtualTree();
}

void UDynamicDataSource::Shutdown()
{
	CollectionManager = nullptr;

	DynamicHierarchy.Reset();

	if (OnEndGeneratorHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Remove(OnEndGeneratorHandle);
	}

	if (OnDynamicClassUpdatedHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.Remove(OnDynamicClassUpdatedHandle);
	}

	Super::Shutdown();
}

void UDynamicDataSource::CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter,
                                       FContentBrowserDataCompiledFilter& OutCompiledFilter)
{
#if UE_F_NAME_PERMISSION_LIST
	const FNamePermissionList* ClassPermissionList = nullptr;
#else
	const FPathPermissionList* ClassPermissionList = nullptr;
#endif

	if (const auto DataClassFilter = InFilter.ExtraFilters.FindFilter<FContentBrowserDataClassFilter>())
	{
		if (DataClassFilter->ClassPermissionList)
		{
			if (DataClassFilter->ClassPermissionList->HasFiltering())
			{
				ClassPermissionList = DataClassFilter->ClassPermissionList.Get();
			}
		}
	}

	const auto bIncludeFolders =
		EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders);

	const auto bIncludeFiles = EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles);

	const auto bIncludeClasses = EnumHasAnyFlags(InFilter.ItemCategoryFilter,
	                                             EContentBrowserItemCategoryFilter::IncludeClasses);

	auto& FilterList = OutCompiledFilter.CompiledFilters.FindOrAdd(this);

	auto& [Classes, Folders] = FilterList.FindOrAddFilter<FDynamicDataFilter>();

	if (!bIncludeClasses || (!bIncludeFolders && !bIncludeFiles))
	{
		return;
	}

	RefreshVirtualPathTreeIfNeeded();

	TSet<FName> InternalPaths;

	FName ConvertInternalPath;

	const auto ContentBrowserPathType = TryConvertVirtualPath(InPath, ConvertInternalPath);

	if (ContentBrowserPathType == EContentBrowserPathType::Internal)
	{
		InternalPaths.Add(ConvertInternalPath);
	}
	else if (ContentBrowserPathType != EContentBrowserPathType::Virtual)
	{
		return;
	}

	if (bIncludeFolders)
	{
		if (InFilter.bRecursivePaths)
		{
			if (ContentBrowserPathType == EContentBrowserPathType::Virtual)
			{
				RootPathVirtualTree.EnumerateSubPaths(InPath,
				                                      [this, &InternalPaths](
				                                      FName VirtualSubPath, FName InternalSubPath)
				                                      {
					                                      if (!InternalSubPath.IsNone())
					                                      {
						                                      if (IsRootInternalPath(InternalSubPath))
						                                      {
							                                      InternalPaths.Add(InternalSubPath);
						                                      }
					                                      }
					                                      return true;
				                                      }, true);
			}
		}
		else
		{
			if (ContentBrowserPathType == EContentBrowserPathType::Virtual)
			{
				FContentBrowserCompiledVirtualFolderFilter* CompiledVirtualFolderFilter = nullptr;

				RootPathVirtualTree.EnumerateSubPaths(InPath,
				                                      [this, &InternalPaths, &CompiledVirtualFolderFilter, &FilterList](
				                                      FName VirtualSubPath, FName InternalSubPath)
				                                      {
					                                      if (!InternalSubPath.IsNone())
					                                      {
						                                      if (IsRootInternalPath(InternalSubPath))
						                                      {
							                                      InternalPaths.Add(InternalSubPath);
						                                      }
					                                      }
					                                      else
					                                      {
						                                      auto bPassesFilter = false;

						                                      RootPathVirtualTree.EnumerateSubPaths(VirtualSubPath,
							                                      [&CompiledVirtualFolderFilter, &FilterList,
								                                      &bPassesFilter](
							                                      FName RecursiveVirtualSubPath,
							                                      FName RecursiveInternalSubPath)
							                                      {
								                                      bPassesFilter = bPassesFilter ||
								                                      (!RecursiveInternalSubPath.IsNone() &&
									                                      IsRootInternalPath(
										                                      RecursiveInternalSubPath));

								                                      return !bPassesFilter;
							                                      }, true);

						                                      if (bPassesFilter)
						                                      {
							                                      if (!CompiledVirtualFolderFilter)
							                                      {
								                                      CompiledVirtualFolderFilter = &FilterList.
									                                      FindOrAddFilter<
										                                      FContentBrowserCompiledVirtualFolderFilter>();
							                                      }

							                                      if (!CompiledVirtualFolderFilter->CachedSubPaths.
								                                      Contains(VirtualSubPath))
							                                      {
								                                      CompiledVirtualFolderFilter->CachedSubPaths.Add(
									                                      VirtualSubPath,
									                                      CreateVirtualFolderItem(VirtualSubPath));
							                                      }
						                                      }
					                                      }
					                                      return true;
				                                      }, false);

				Folders.Append(InternalPaths);

				return;
			}
		}
	}
	else if (bIncludeFiles)
	{
		if (InFilter.bRecursivePaths)
		{
			if (ContentBrowserPathType == EContentBrowserPathType::Virtual)
			{
				RootPathVirtualTree.EnumerateSubPaths(InPath,
				                                      [this, &InternalPaths](
				                                      FName VirtualSubPath, FName InternalSubPath)
				                                      {
					                                      if (!InternalSubPath.IsNone())
					                                      {
						                                      if (IsRootInternalPath(InternalSubPath))
						                                      {
							                                      InternalPaths.Add(InternalSubPath);
						                                      }
					                                      }

					                                      return true;
				                                      }, true);

				if (InternalPaths.IsEmpty())
				{
					return;
				}
			}
		}
		else
		{
			if (ContentBrowserPathType == EContentBrowserPathType::Virtual)
			{
				return;
			}
		}
	}

	if (InternalPaths.IsEmpty() || !DynamicHierarchy.IsValid())
	{
		return;
	}

	if (bIncludeFolders)
	{
		const auto& MatchingFolders = DynamicHierarchy->GetMatchingFolders(
			ConvertInternalPath, InFilter.bRecursivePaths);

		if (ContentBrowserPathType == EContentBrowserPathType::Virtual)
		{
			for (const auto& InternalPath : InternalPaths)
			{
				Folders.Add(InternalPath);
			}
		}

		for (const auto& MatchingFolder : MatchingFolders)
		{
			Folders.Add(MatchingFolder);
		}
	}

	if (bIncludeFiles)
	{
		if (const auto& MatchingClasses = DynamicHierarchy->GetMatchingClasses(
			ConvertInternalPath, InFilter.bRecursivePaths); !MatchingClasses.IsEmpty())
		{
#if UE_F_TOP_LEVEL_ASSET_PATH
			TSet<FTopLevelAssetPath> ClassPathsToInclude;
#else
			TSet<FName> ClassPathsToInclude;
#endif

			if (const auto DataCollectionFilter = InFilter.ExtraFilters.FindFilter<
				FContentBrowserDataCollectionFilter>())
			{
#if UE_F_TOP_LEVEL_ASSET_PATH
				TArray<FTopLevelAssetPath> ClassPathsForCollections;
#else
				TArray<FName> ClassPathsForCollections;
#endif

				if (GetClassPaths(DataCollectionFilter->SelectedCollections,
				                  DataCollectionFilter->bIncludeChildCollections,
				                  ClassPathsForCollections) &&
					ClassPathsForCollections.IsEmpty())
				{
					return;
				}

				ClassPathsToInclude.Append(ClassPathsForCollections);
			}

			for (auto MatchingClass : MatchingClasses)
			{
				const auto bPassesInclusiveFilter = ClassPathsToInclude.IsEmpty() ||
					ClassPathsToInclude.Contains(
#if UE_F_TOP_LEVEL_ASSET_PATH
						FTopLevelAssetPath(MatchingClass));
#else
						*MatchingClass->GetPathName());
#endif

				const auto bPassesPermissionCheck = !ClassPermissionList ||
					ClassPermissionList->PassesFilter(
#if UE_F_TOP_LEVEL_ASSET_PATH
						MatchingClass->GetClassPathName().ToString());
#else
						MatchingClass->GetFName());
#endif

				if (bPassesInclusiveFilter && bPassesPermissionCheck)
				{
					Classes.Add(MatchingClass);
				}
			}
		}
	}
}

void UDynamicDataSource::EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter,
                                                      TFunctionRef<bool(FContentBrowserItemData&&)> InCallback)
{
	const auto DataFilterList = InFilter.CompiledFilters.Find(this);

	if (!DataFilterList)
	{
		return;
	}

	const auto ClassDataFilter = DataFilterList->FindFilter<FDynamicDataFilter>();

	if (!ClassDataFilter)
	{
		return;
	}

	if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders))
	{
		for (const auto& Folder : ClassDataFilter->Folders)
		{
			if (!InCallback(CreateFolderItemDataPayload(Folder)))
			{
				return;
			}
		}
	}

	if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles))
	{
		for (const auto Class : ClassDataFilter->Classes)
		{
			if (!InCallback(CreateFileItemDataPayload(Class)))
			{
				return;
			}
		}
	}
}

void UDynamicDataSource::EnumerateItemsAtPath(const FName InPath,
                                              const EContentBrowserItemTypeFilter InItemTypeFilter,
                                              TFunctionRef<bool(FContentBrowserItemData&&)> InCallback)
{
	FName InternalPath;

	if (!TryConvertVirtualPathToInternal(InPath, InternalPath))
	{
		return;
	}

	if (EnumHasAnyFlags(InItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders))
	{
		if (DynamicHierarchy->FindNode(InternalPath))
		{
			InCallback(CreateFolderItemDataPayload(InternalPath));
		}
	}

	if (EnumHasAnyFlags(InItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles))
	{
		if (const auto Node = DynamicHierarchy->FindNode(InternalPath))
		{
			for (const auto Class : Node->GetClasses())
			{
				InCallback(CreateFileItemDataPayload(Class));
			}
		}
	}
}

bool UDynamicDataSource::EnumerateItemsForObjects(const TArrayView<UObject*> InObjects,
                                                  TFunctionRef<bool(FContentBrowserItemData&&)> InCallback)
{
	for (const auto Object : InObjects)
	{
		if (const auto Class = Cast<UClass>(Object))
		{
			if (!InCallback(CreateFileItemDataPayload(Class)))
			{
				return false;
			}
		}
	}

	return true;
}

bool UDynamicDataSource::DoesItemPassFilter(const FContentBrowserItemData& InItem,
                                            const FContentBrowserDataCompiledFilter& InFilter)
{
	const auto DataFilterList = InFilter.CompiledFilters.Find(this);

	if (!DataFilterList)
	{
		return false;
	}

	const auto ClassDataFilter = DataFilterList->FindFilter<FDynamicDataFilter>();

	if (!ClassDataFilter)
	{
		return false;
	}

	switch (InItem.GetItemType())
	{
	case EContentBrowserItemFlags::Type_Folder:
		{
			if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders) &&
				!ClassDataFilter->Folders.IsEmpty())
			{
				if (const auto FolderItemDataPayload = GetFolderItemDataPayload(InItem))
				{
					return ClassDataFilter->Folders.Contains(FolderItemDataPayload->GetInternalPath());
				}
			}
		}
		break;

	case EContentBrowserItemFlags::Type_File:
		{
			if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles) &&
				!ClassDataFilter->Classes.IsEmpty())
			{
				if (const auto FileItemDataPayload = GetFileItemDataPayload(InItem))
				{
					return ClassDataFilter->Classes.Contains(FileItemDataPayload->GetClass());
				}
			}
		}
		break;

	default:
		break;
	}

	return false;
}

bool UDynamicDataSource::GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData,
                                          const FName InAttributeKey,
                                          FContentBrowserItemDataAttributeValue& OutAttributeValue)
{
	const auto FileItemDataPayload = GetFileItemDataPayload(InItem);

	return FileItemDataPayload ? FileItemDataPayload->GetItemAttribute(InAttributeKey, OutAttributeValue) : false;
}

bool UDynamicDataSource::CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg)
{
	return true;
}

bool UDynamicDataSource::EditItem(const FContentBrowserItemData& InItem)
{
	const auto ItemDataPayload = GetFileItemDataPayload(InItem);

	return ItemDataPayload
		       ? FSourceCodeNavigation::OpenSourceFile(ItemDataPayload->GetInternalPath().ToString())
		       : false;
}

bool UDynamicDataSource::BulkEditItems(TArrayView<const FContentBrowserItemData> InItems)
{
	for (const auto& Item : InItems)
	{
		EditItem(Item);
	}

	return true;
}


bool UDynamicDataSource::AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr)
{
	if (const auto FileItemDataPayload = GetFileItemDataPayload(InItem))
	{
		if (!InOutStr.IsEmpty())
		{
			InOutStr += LINE_TERMINATOR;
		}

		InOutStr += FileItemDataPayload->GetAssetData().GetExportTextName();

		return true;
	}

	return false;
}

bool UDynamicDataSource::UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail)
{
	if (const auto FileItemDataPayload = GetFileItemDataPayload(InItem))
	{
		FileItemDataPayload->UpdateThumbnail(InThumbnail);

		return true;
	}

	return false;
}

bool UDynamicDataSource::TryGetCollectionId(const FContentBrowserItemData& InItem,
#if UE_TRY_GET_COLLECTION_ID_F_SOFT_OBJECT_PATH
                                            FName& OutCollectionId)
#else
                                            FSoftObjectPath& OutCollectionId)
#endif
{
	if (const auto FileItemPayload = GetFileItemDataPayload(InItem))
	{
#if UE_ASSET_DATA_GET_SOFT_OBJECT_PATH
		OutCollectionId = FSoftObjectPath(FileItemPayload->GetAssetData().GetSoftObjectPath());
#else
		OutCollectionId = FileItemPayload->GetAssetData().ObjectPath;
#endif

		return true;
	}

	return false;
}

bool UDynamicDataSource::Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath)
{
	if (const auto FolderItemDataPayload = GetFolderItemDataPayload(InItem))
	{
		OutPackagePath = FolderItemDataPayload->GetInternalPath();

		return true;
	}

	return false;
}

bool UDynamicDataSource::Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData)
{
	if (const auto FileItemPayload = GetFileItemDataPayload(InItem))
	{
		OutAssetData = FileItemPayload->GetAssetData();

		return true;
	}

	return false;
}

bool UDynamicDataSource::Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath)
{
	return TryConvertInternalPathToVirtual(InPackagePath, OutPath);
}

bool UDynamicDataSource::Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData,
                                                                 const bool InUseFolderPaths, FName& OutPath)
{
	return TryConvertInternalPathToVirtual(
#if UE_ASSET_DATA_GET_SOFT_OBJECT_PATH
		InUseFolderPaths ? InAssetData.PackagePath : *InAssetData.GetSoftObjectPath().ToString(),
#else
		InUseFolderPaths ? InAssetData.PackagePath : InAssetData.ObjectPath,
#endif
		OutPath);
}

void UDynamicDataSource::BuildRootPathVirtualTree()
{
	Super::BuildRootPathVirtualTree();

	RootPathAdded(FNameBuilder(*DYNAMIC_ROOT_INTERNAL_PATH));
}

void UDynamicDataSource::OnDynamicClassUpdated()
{
	UpdateHierarchy();
}

void UDynamicDataSource::OnEndGenerator()
{
	UpdateHierarchy();
}

void UDynamicDataSource::UpdateHierarchy()
{
	DynamicHierarchy.Reset();

	DynamicHierarchy = MakeShareable(new FDynamicHierarchy());

	SetVirtualPathTreeNeedsRebuild();

	NotifyItemDataRefreshed();
}

bool UDynamicDataSource::IsRootInternalPath(const FName& InPath)
{
	return InPath.ToString().StartsWith(DYNAMIC_ROOT_INTERNAL_PATH);
}

FString UDynamicDataSource::GetVirtualPath(const UClass* InClass)
{
	return InClass != nullptr ? DYNAMIC_ROOT_VIRTUAL_PATH / InClass->GetFName().ToString() : FString();
}

TSharedPtr<const FDynamicFileItemDataPayload> UDynamicDataSource::GetFileItemDataPayload(
	const FContentBrowserItemData& InItemData) const
{
	return InItemData.GetOwnerDataSource() == this && InItemData.IsFile()
		       ? StaticCastSharedPtr<const FDynamicFileItemDataPayload>(InItemData.GetPayload())
		       : nullptr;
}

TSharedPtr<const FDynamicFolderItemDataPayload> UDynamicDataSource::GetFolderItemDataPayload(
	const FContentBrowserItemData& InItemData) const
{
	return InItemData.GetOwnerDataSource() == this && InItemData.IsFolder()
		       ? StaticCastSharedPtr<const FDynamicFolderItemDataPayload>(InItemData.GetPayload())
		       : nullptr;
}

FContentBrowserItemData UDynamicDataSource::CreateFolderItemDataPayload(const FName& InFolderPath)
{
	FName VirtualPath;

	TryConvertInternalPathToVirtual(InFolderPath, VirtualPath);

	const auto FolderItemName = FPackageName::GetShortName(InFolderPath);

	FText DisplayNameOverride;

	if (InFolderPath == *DYNAMIC_ROOT_INTERNAL_PATH)
	{
		DisplayNameOverride = LOCTEXT("DynamicFolderDisplayName", "Dynamic Classes");
	}
	else
	{
		DisplayNameOverride = ContentBrowserDataUtils::GetFolderItemDisplayNameOverride(
			InFolderPath, FolderItemName, true);
	}

	return FContentBrowserItemData(this,
	                               EContentBrowserItemFlags::Type_Folder | EContentBrowserItemFlags::Category_Class
#if UE_E_CONTENT_BROWSER_ITEM_FLAGS_CATEGORY_PLUGIN
	                               | EContentBrowserItemFlags::Category_Plugin
#endif
	                               ,
	                               VirtualPath,
	                               *FolderItemName,
	                               MoveTemp(DisplayNameOverride),
	                               MakeShared<FDynamicFolderItemDataPayload>(InFolderPath));
}

FContentBrowserItemData UDynamicDataSource::CreateFileItemDataPayload(UClass* InClass)
{
	return FContentBrowserItemData(this,
	                               EContentBrowserItemFlags::Type_File | EContentBrowserItemFlags::Category_Class
#if UE_E_CONTENT_BROWSER_ITEM_FLAGS_CATEGORY_PLUGIN
	                               | EContentBrowserItemFlags::Category_Plugin
#endif
	                               ,
	                               *GetVirtualPath(InClass),
	                               InClass->GetFName(),
	                               FText(),
	                               MakeShared<FDynamicFileItemDataPayload>(
		                               *FDynamicGenerator::GetDynamicNormalizeFile(InClass), InClass));
}

bool UDynamicDataSource::GetClassPaths(const TArrayView<const FCollectionNameType>& InCollections,
                                       const bool bIncludeChildCollections,
#if UE_F_TOP_LEVEL_ASSET_PATH
                                       TArray<FTopLevelAssetPath>& OutClassPaths) const
#else
                                       TArray<FName>& OutClassPaths) const
#endif
{
	if (!InCollections.IsEmpty())
	{
		const auto CollectionRecursionFlags = bIncludeChildCollections
			                                      ? ECollectionRecursionFlags::SelfAndChildren
			                                      : ECollectionRecursionFlags::Self;

		for (const auto& [Name, Type] : InCollections)
		{
			CollectionManager->GetClassesInCollection(Name, Type, OutClassPaths, CollectionRecursionFlags);
		}

		return true;
	}

	return false;
}

#undef LOCTEXT_NAMESPACE
