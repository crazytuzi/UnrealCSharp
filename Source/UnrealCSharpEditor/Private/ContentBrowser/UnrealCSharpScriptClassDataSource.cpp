#include "ContentBrowser/UnrealCSharpScriptClassDataSource.h"

#include "AssetToolsModule.h"
#include "CollectionManagerModule.h"
#include "ContentBrowserDataUtils.h"
#include "ContentBrowserItemPath.h"
#include "ProjectDescriptor.h"
#include "SourceCodeNavigation.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Interfaces/IProjectManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UnrealCSharpScriptClassDataSource)

#define LOCTEXT_NAMESPACE "UnrealCSharpScriptClassDataSource"

void UUnrealCSharpScriptClassDataSource::Initialize(const bool InAutoRegister)
{
	Super::Initialize(InAutoRegister);

	FUnrealCSharpCoreModuleDelegates::OnClassHierarchyUpdated.AddUObject(
		this, &UUnrealCSharpScriptClassDataSource::OnScriptClassHierarchyUpdated);

	CollectionManager = &FCollectionManagerModule::GetModule().Get();

	BuildRootPathVirtualTree();
}

void UUnrealCSharpScriptClassDataSource::Shutdown()
{
	Super::Shutdown();

	CollectionManager = nullptr;

	ScriptClassHierarchy.Reset();

	ClassTypeActions.Reset();
}

TSharedPtr<IAssetTypeActions> UUnrealCSharpScriptClassDataSource::GetClassTypeActions()
{
	if (!ClassTypeActions)
	{
		static const FName NAME_AssetTools = "AssetTools";

		const auto& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(
			NAME_AssetTools);

		ClassTypeActions = AssetToolsModule.Get().GetAssetTypeActionsForClass(UClass::StaticClass()).Pin();
	}

	return ClassTypeActions;
}

bool UUnrealCSharpScriptClassDataSource::RootClassPathPassesFilter(const FName InRootClassPath)
{
	return InRootClassPath.ToString().StartsWith(SCRIPT_CLASS_ROOT_INTERNAL_PATH);
}

void UUnrealCSharpScriptClassDataSource::BuildRootPathVirtualTree()
{
	Super::BuildRootPathVirtualTree();

	RootPathAdded(FNameBuilder(TEXT(SCRIPT_CLASS_ROOT_INTERNAL_PATH)));
}

void UUnrealCSharpScriptClassDataSource::CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter,
                                                       FContentBrowserDataCompiledFilter& OutCompiledFilter)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UUnrealCSharpScriptClassDataSource::CompileFilter);

	const auto ClassFilter = InFilter.ExtraFilters.FindFilter<FContentBrowserDataClassFilter>();

	const auto CollectionFilter = InFilter.ExtraFilters.FindFilter<FContentBrowserDataCollectionFilter>();

	const auto ClassPermissionList = ClassFilter && ClassFilter->ClassPermissionList && ClassFilter->
	                                 ClassPermissionList->HasFiltering()
		                                 ? ClassFilter->ClassPermissionList.Get()
		                                 : nullptr;

	const bool bIncludeFolders =
		EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders);

	const bool bIncludeFiles = EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles);

	const bool bIncludeClasses = EnumHasAnyFlags(InFilter.ItemCategoryFilter,
	                                             EContentBrowserItemCategoryFilter::IncludeClasses);

	auto& FilterList = OutCompiledFilter.CompiledFilters.FindOrAdd(this);

	auto& ScriptClassDataFilter = FilterList.FindOrAddFilter<FUnrealCSharpCompiledScriptClassDataFilter>();

	if (!bIncludeClasses || (!bIncludeFolders && !bIncludeFiles))
	{
		return;
	}

	TSet<FName> InternalPaths;

	FName ConvertedPath;

	const auto ConvertedPathType = TryConvertVirtualPath(InPath, ConvertedPath);

	if (ConvertedPathType == EContentBrowserPathType::Internal)
	{
		InternalPaths.Add(ConvertedPath);
	}
	else if (ConvertedPathType != EContentBrowserPathType::Virtual)
	{
		return;
	}

	if (bIncludeFolders)
	{
		if (InFilter.bRecursivePaths)
		{
			if (ConvertedPathType == EContentBrowserPathType::Virtual)
			{
				RootPathVirtualTree.EnumerateSubPaths(
					InPath, [this, &InternalPaths](FName VirtualSubPath, FName InternalSubPath)
					{
						if (!InternalSubPath.IsNone())
						{
							if (RootClassPathPassesFilter(InternalSubPath))
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
			if (ConvertedPathType == EContentBrowserPathType::Virtual)
			{
				FContentBrowserCompiledVirtualFolderFilter* VirtualFolderFilter = nullptr;
				RootPathVirtualTree.EnumerateSubPaths(
					InPath, [this, &InternalPaths, &VirtualFolderFilter, &FilterList](
					FName VirtualSubPath, FName InternalSubPath)
					{
						if (!InternalSubPath.IsNone())
						{
							if (RootClassPathPassesFilter(InternalSubPath))
							{
								InternalPaths.Add(InternalSubPath);
							}
						}
						else
						{
							bool bPassesFilter = false;

							RootPathVirtualTree.EnumerateSubPaths(VirtualSubPath,
							                                      [this, &VirtualFolderFilter, &FilterList, &
								                                      bPassesFilter](
							                                      FName RecursiveVirtualSubPath,
							                                      FName RecursiveInternalSubPath)
							                                      {
								                                      bPassesFilter = bPassesFilter || (!
									                                      RecursiveInternalSubPath.IsNone() &&
									                                      RootClassPathPassesFilter(
										                                      RecursiveInternalSubPath));
								                                      return bPassesFilter == false;
							                                      }, true);

							if (bPassesFilter)
							{
								if (!VirtualFolderFilter)
								{
									VirtualFolderFilter = &FilterList.FindOrAddFilter<
										FContentBrowserCompiledVirtualFolderFilter>();
								}

								if (!VirtualFolderFilter->CachedSubPaths.Contains(VirtualSubPath))
								{
									VirtualFolderFilter->CachedSubPaths.Add(
										VirtualSubPath, CreateVirtualFolderItem(VirtualSubPath));
								}
							}
						}
						return true;
					}, false);

				ScriptClassDataFilter.ValidFolders.Append(InternalPaths);
				return;
			}
		}
	}
	else if (bIncludeFiles)
	{
		if (InFilter.bRecursivePaths)
		{
			if (ConvertedPathType == EContentBrowserPathType::Virtual)
			{
				RootPathVirtualTree.EnumerateSubPaths(
					InPath, [this, &InternalPaths](FName VirtualSubPath, FName InternalSubPath)
					{
						if (!InternalSubPath.IsNone())
						{
							if (RootClassPathPassesFilter(InternalSubPath))
							{
								InternalPaths.Add(InternalSubPath);
							}
						}
						return true;
					}, true);

				if (InternalPaths.Num() == 0)
				{
					return;
				}
			}
		}
		else
		{
			if (ConvertedPathType == EContentBrowserPathType::Virtual)
			{
				return;
			}
		}
	}

	if (InternalPaths.Num() == 0 || !ScriptClassHierarchy.IsValid())
	{
		return;
	}

	if (bIncludeFolders)
	{
		auto ChildClassFolders = ScriptClassHierarchy->GetMatchingFolders(
			ConvertedPath, InFilter.bRecursivePaths);

		if (ConvertedPathType == EContentBrowserPathType::Virtual)
		{
			for (const FName InternalPath : InternalPaths)
			{
				ScriptClassDataFilter.ValidFolders.Add(InternalPath);
			}
		}

		for (const FName ChildClassFolder : ChildClassFolders)
		{
			ScriptClassDataFilter.ValidFolders.Add(ChildClassFolder);
		}
	}

	if (bIncludeFiles)
	{
		if (const auto ChildClassObjects = ScriptClassHierarchy->GetMatchingClasses(
			ConvertedPath, InFilter.bRecursivePaths); ChildClassObjects.Num() > 0)
		{
			TSet<FTopLevelAssetPath> ClassPathsToInclude;

			if (CollectionFilter)
			{
				TArray<FTopLevelAssetPath> ClassPathsForCollections;
				if (GetClassPathsForCollections(CollectionFilter->SelectedCollections,
				                                CollectionFilter->bIncludeChildCollections,
				                                ClassPathsForCollections) && ClassPathsForCollections.Num() == 0)
				{
					return;
				}

				ClassPathsToInclude.Append(ClassPathsForCollections);
			}

			for (UClass* ChildClassObject : ChildClassObjects)
			{
				const bool bPassesInclusiveFilter = ClassPathsToInclude.Num() == 0 || ClassPathsToInclude.Contains(
					FTopLevelAssetPath(ChildClassObject));

				const bool bPassesPermissionCheck = !ClassPermissionList || ClassPermissionList->PassesFilter(
					ChildClassObject->GetClassPathName().ToString());

				if (bPassesInclusiveFilter && bPassesPermissionCheck)
				{
					ScriptClassDataFilter.ValidClasses.Add(ChildClassObject);
				}
			}
		}
	}
}

FContentBrowserItemData UUnrealCSharpScriptClassDataSource::CreateClassFolderItem(const FName InFolderPath)
{
	FName VirtualizedPath;

	TryConvertInternalPathToVirtual(InFolderPath, VirtualizedPath);

	const FString FolderItemName = FPackageName::GetShortName(InFolderPath);

	FText FolderDisplayNameOverride;

	if (InFolderPath == TEXT(SCRIPT_CLASS_ROOT_INTERNAL_PATH))
	{
		FolderDisplayNameOverride = LOCTEXT("ScriptFolderDisplayName", "Script Classes");
	}
	else
	{
		FolderDisplayNameOverride = ContentBrowserDataUtils::GetFolderItemDisplayNameOverride(
			InFolderPath, FolderItemName, true);
	}

	return FContentBrowserItemData(this,
	                               EContentBrowserItemFlags::Type_Folder | EContentBrowserItemFlags::Category_Class |
	                               EContentBrowserItemFlags::Category_Plugin,
	                               VirtualizedPath,
	                               *FolderItemName,
	                               MoveTemp(FolderDisplayNameOverride),
	                               MakeShared<FUnrealCSharpScriptClassFolderItemDataPayload>(InFolderPath));
}

FContentBrowserItemData UUnrealCSharpScriptClassDataSource::CreateClassFileItem(UClass* InClass)
{
	return FContentBrowserItemData(this,
	                               EContentBrowserItemFlags::Type_File | EContentBrowserItemFlags::Category_Class |
	                               EContentBrowserItemFlags::Category_Plugin,
	                               *GetDynamicClassVirtualPath(InClass),
	                               InClass->GetFName(),
	                               FText(),
	                               MakeShared<FUnrealCSharpScriptClassFileItemDataPayload>(
		                               *GetDynamicClassSourcePath(InClass), InClass));
}

void UUnrealCSharpScriptClassDataSource::EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter,
                                                                      TFunctionRef<bool(FContentBrowserItemData&&)>
                                                                      InCallback)
{
	const auto FilterList = InFilter.CompiledFilters.Find(this);

	if (!FilterList)
	{
		return;
	}

	const auto ClassDataFilter = FilterList->FindFilter<FUnrealCSharpCompiledScriptClassDataFilter>();

	if (!ClassDataFilter)
	{
		return;
	}

	if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders))
	{
		for (const FName ValidFolder : ClassDataFilter->ValidFolders)
		{
			if (!InCallback(CreateClassFolderItem(ValidFolder)))
			{
				return;
			}
		}
	}

	if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles))
	{
		for (UClass* ValidClass : ClassDataFilter->ValidClasses)
		{
			if (!InCallback(CreateClassFileItem(ValidClass)))
			{
				return;
			}
		}
	}
}

void UUnrealCSharpScriptClassDataSource::EnumerateItemsAtPath(const FName InPath,
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
		if (auto FolderNode = ScriptClassHierarchy->FindNodeByPath(InternalPath))
		{
			InCallback(CreateClassFolderItem(InternalPath));
		}
	}

	if (EnumHasAnyFlags(InItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles))
	{
		if (const auto FolderNode = ScriptClassHierarchy->FindNodeByPath(
			InternalPath))
		{
			for (const auto ChildClass : FolderNode->ChildScriptClasses)
			{
				InCallback(CreateClassFileItem(ChildClass));
			}
		}
	}
}

bool UUnrealCSharpScriptClassDataSource::EnumerateItemsForObjects(const TArrayView<UObject*> InObjects,
                                                                  TFunctionRef<bool(FContentBrowserItemData&&)>
                                                                  InCallback)
{
	FString InternalPath;

	for (UObject* InObject : InObjects)
	{
		if (UClass* InClass = Cast<UClass>(InObject))
		{
			if (!InCallback(CreateClassFileItem(InClass)))
			{
				return false;
			}
		}
	}

	return true;
}

bool UUnrealCSharpScriptClassDataSource::DoesItemPassFilter(const FContentBrowserItemData& InItem,
                                                            const FContentBrowserDataCompiledFilter& InFilter)
{
	const auto FilterList = InFilter.CompiledFilters.Find(this);

	if (!FilterList)
	{
		return false;
	}

	const auto ClassDataFilter = FilterList->FindFilter<FUnrealCSharpCompiledScriptClassDataFilter>();

	if (!ClassDataFilter)
	{
		return false;
	}

	switch (InItem.GetItemType())
	{
	case EContentBrowserItemFlags::Type_Folder:
		if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFolders) && ClassDataFilter->
			ValidFolders.Num() > 0)
		{
			if (const auto FolderPayload = GetClassFolderItemDataPayload(InItem))
			{
				return ClassDataFilter->ValidFolders.Contains(FolderPayload->GetInternalPath());
			}
		}
		break;

	case EContentBrowserItemFlags::Type_File:
		if (EnumHasAnyFlags(InFilter.ItemTypeFilter, EContentBrowserItemTypeFilter::IncludeFiles) && ClassDataFilter->
			ValidClasses.Num() > 0)
		{
			if (const auto ClassPayload = GetClassFileItemPayload(InItem))
			{
				return ClassDataFilter->ValidClasses.Contains(ClassPayload->GetClass());
			}
		}
		break;

	default:
		break;
	}

	return false;
}

FName UUnrealCSharpScriptClassDataSource::GetClassModuleName(const UClass* InClass)
{
	if (const UPackage* ClassPackage = InClass->GetOuterUPackage(); ClassPackage)
	{
		return FPackageName::GetShortFName(ClassPackage->GetFName());
	}

	return NAME_None;
}

TSet<FName> UUnrealCSharpScriptClassDataSource::GetGameModules()
{
	TSet<FName> GameModules;

	if (FApp::HasProjectName())
	{
		if (const auto CurrentProject = IProjectManager::Get().GetCurrentProject())
		{
			for (const auto Module : CurrentProject->Modules)
			{
				GameModules.Add(Module.Name);
			}
		}
	}

	return GameModules;
}

FString UUnrealCSharpScriptClassDataSource::GetDynamicClassSourcePath(const UClass* InClass)
{
	return FDynamicGenerator::GetDynamicFile(InClass).Replace(TEXT("\\"), TEXT("/"));
}

FString UUnrealCSharpScriptClassDataSource::GetDynamicClassVirtualPath(const UClass* InClass)
{
	if (InClass)
	{
		return SCRIPT_CLASS_ROOT_VIRTUAL_PATH + FString::Printf(TEXT("/%s"), *InClass->GetFName().ToString());
	}

	return FString();
}

bool UUnrealCSharpScriptClassDataSource::CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg)
{
	return true;
}

bool UUnrealCSharpScriptClassDataSource::EditItem(const FContentBrowserItemData& InItem)
{
	if (const auto ItemDataPayload = GetClassFileItemPayload(InItem))
	{
		const FString InternalPath = ItemDataPayload->GetInternalPath().ToString();

		return FSourceCodeNavigation::OpenSourceFile(InternalPath);
	}
	return false;
}

bool UUnrealCSharpScriptClassDataSource::BulkEditItems(TArrayView<const FContentBrowserItemData> InItems)
{
	for (auto Item : InItems)
	{
		EditItem(Item);
	}
	return true;
}

bool UUnrealCSharpScriptClassDataSource::UpdateThumbnail(const FContentBrowserItemData& InItem,
                                                         FAssetThumbnail& InThumbnail)
{
	if (const auto ClassPayload = GetClassFileItemPayload(InItem))
	{
		ClassPayload->UpdateThumbnail(InThumbnail);

		return true;
	}
	return false;
}

bool UUnrealCSharpScriptClassDataSource::GetItemAttribute(const FContentBrowserItemData& InItem,
                                                          const bool InIncludeMetaData, const FName InAttributeKey,
                                                          FContentBrowserItemDataAttributeValue& OutAttributeValue)
{
	if (const auto ClassPayload = GetClassFileItemPayload(InItem))
	{

		return ClassPayload->GetClassFileItemAttribute(GetClassTypeActions().Get(), InIncludeMetaData, InAttributeKey, OutAttributeValue);
	}

	return false;
}

bool UUnrealCSharpScriptClassDataSource::AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr)
{
	if (const auto ClassPayload = GetClassFileItemPayload(InItem))
	{
		if (InOutStr.Len() > 0)
		{
			InOutStr += LINE_TERMINATOR;
		}
		
		InOutStr += ClassPayload->GetAssetData().GetExportTextName();
		
		return true;
	}

	return false;
}

bool UUnrealCSharpScriptClassDataSource::TryGetCollectionId(const FContentBrowserItemData& InItem,
                                                            FSoftObjectPath& OutCollectionId)
{
	if (const auto ClassPayload = GetClassFileItemPayload(InItem))
	{
		OutCollectionId = FSoftObjectPath(ClassPayload->GetAssetData().GetSoftObjectPath());

		return true;
	}

	return false;
}

bool UUnrealCSharpScriptClassDataSource::Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem,
                                                                  FName& OutPackagePath)
{
	if (const auto FolderPayload = GetClassFolderItemDataPayload(InItem))
	{
		OutPackagePath = FolderPayload->GetInternalPath();

		return true;
	}

	return false;
}

bool UUnrealCSharpScriptClassDataSource::Legacy_TryGetAssetData(const FContentBrowserItemData& InItem,
                                                                FAssetData& OutAssetData)
{
	if (const auto ClassPayload = GetClassFileItemPayload(InItem))
	{
		OutAssetData = ClassPayload->GetAssetData();

		return true;
	}

	return false;
}

bool UUnrealCSharpScriptClassDataSource::Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath,
	FName& OutPath)
{
	return TryConvertInternalPathToVirtual(InPackagePath, OutPath);
}

bool UUnrealCSharpScriptClassDataSource::Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData,
	const bool InUseFolderPaths, FName& OutPath)
{
	return TryConvertInternalPathToVirtual(
		InUseFolderPaths ? InAssetData.PackagePath : *InAssetData.GetSoftObjectPath().ToString(),
		OutPath);
}

TSharedPtr<const FUnrealCSharpScriptClassFileItemDataPayload>
UUnrealCSharpScriptClassDataSource::GetClassFileItemPayload(const FContentBrowserItemData& InItem) const
{
	if (InItem.GetOwnerDataSource() == this && InItem.IsFile())
	{
		return StaticCastSharedPtr<const FUnrealCSharpScriptClassFileItemDataPayload>(InItem.GetPayload());
	}

	return nullptr;
}

TSharedPtr<const FUnrealCSharpScriptClassFolderItemDataPayload>
UUnrealCSharpScriptClassDataSource::GetClassFolderItemDataPayload(const FContentBrowserItemData& InItem) const
{
	if (InItem.GetOwnerDataSource() == this && InItem.IsFolder())
	{
		return StaticCastSharedPtr<const FUnrealCSharpScriptClassFolderItemDataPayload>(InItem.GetPayload());
	}

	return nullptr;
}

bool UUnrealCSharpScriptClassDataSource::GetClassPathsForCollections(
	TArrayView<const FCollectionNameType> InCollections, const bool bIncludeChildCollections,
	TArray<FTopLevelAssetPath>& OutClassPaths) const
{
	if (InCollections.Num() > 0)
	{
		const ECollectionRecursionFlags::Flags CollectionRecursionMode = bIncludeChildCollections
			                                                                 ? ECollectionRecursionFlags::SelfAndChildren
			                                                                 : ECollectionRecursionFlags::Self;

		for (const FCollectionNameType& CollectionNameType : InCollections)
		{
			CollectionManager->GetClassesInCollection(CollectionNameType.Name, CollectionNameType.Type, OutClassPaths,
			                                          CollectionRecursionMode);
		}

		return true;
	}

	return false;
}

void UUnrealCSharpScriptClassDataSource::OnScriptClassHierarchyUpdated()
{
	ScriptClassHierarchy.Reset();

	ScriptClassHierarchy = MakeShareable(new FScriptClassHierarchy());
}

bool UUnrealCSharpScriptClassDataSource::ConvertRelativePathToVirtualPath(const FName InNativePath,
                                                                          FName& OutVirtualPath)
{
	if (InNativePath == TEXT("/") || InNativePath.IsNone())
	{
		return false;
	}

	OutVirtualPath = *(SCRIPT_CLASS_ROOT_INTERNAL_PATH + InNativePath.ToString());

	return true;
}

bool UUnrealCSharpScriptClassDataSource::EnumerateSubPaths(const FString& InPath,
                                                           const TFunctionRef<bool(FName)>& InCallback)
{
	const TCHAR* PathStr = *InPath;

	const TCHAR* PathStrEnd = PathStr + InPath.Len();

	const TCHAR* PathCharPtr = PathStr + 1;

	for (;;)
	{
		if (PathCharPtr >= PathStrEnd || *PathCharPtr == TEXT('/'))
		{
			if (const FName CheckPath(static_cast<int32>(PathCharPtr - PathStr), PathStr); !CheckPath.IsNone())
			{
				if (!InCallback(CheckPath))
				{
					return false;
				}
			}
		}

		if (PathCharPtr >= PathStrEnd)
		{
			break;
		}

		++PathCharPtr;
	}

	return true;
}

bool UUnrealCSharpScriptClassDataSource::RootPathFilter(const FName& InPath)
{
	const FString ItemPath = InPath.ToString();

	return RootPathFilter(ItemPath);
}

bool UUnrealCSharpScriptClassDataSource::RootPathFilter(const FString& InPath)
{
	if (InPath.StartsWith(FUnrealCSharpFunctionLibrary::GetGameDirectory()))
	{
		return true;
	}

	for (auto CustomProjectDir : FUnrealCSharpFunctionLibrary::GetCustomProjectsDirectory())
	{
		if (InPath.StartsWith(CustomProjectDir))
		{
			return true;
		}
	}

	return false;
}

#undef LOCTEXT_NAMESPACE
