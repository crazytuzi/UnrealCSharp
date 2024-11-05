#pragma once

#include "ContentBrowser/ScriptClassHierarchy.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "ContentBrowser/UnrealCSharpScriptClassDataSource.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicClassGenerator.h"


TSharedPtr<FScriptClassHierarchyNode> FScriptClassHierarchyNode::MakeNode(FName InFileName)
{
	TSharedPtr<FScriptClassHierarchyNode> Node = MakeShareable(new FScriptClassHierarchyNode());

	Node->FileName = MoveTemp(InFileName);

	return Node;
}

FScriptClassHierarchy::FScriptClassHierarchy()
{
	PopulateHierarchy();
}

void FScriptClassHierarchy::BuildTreeRecurseFromClass(UClass* InClass) const
{
	if (InClass == nullptr)
	{
		return;
	}

	if (const FString FolderFileName = FPaths::GetPath(
			UUnrealCSharpScriptClassDataSource::GetDynamicClassSourcePath(InClass));
		UUnrealCSharpScriptClassDataSource::RootPathFilter(FolderFileName))
	{
		const FString FolderRelativePath = FolderFileName.RightChop(
			FUnrealCSharpFunctionLibrary::GetFullScriptDirectory().Len());

		auto CurrentNode = RootNode;

		UUnrealCSharpScriptClassDataSource::EnumerateSubPaths(FolderRelativePath,
		                                                      [this , &CurrentNode](const FName SubVirtualPath)
		                                                      {
			                                                      auto& ChildNode = CurrentNode->GetChildrenRef().
				                                                      FindOrAdd(SubVirtualPath);

			                                                      if (!ChildNode.IsValid())
			                                                      {
				                                                      ChildNode = FScriptClassHierarchyNode::MakeNode(
					                                                      SubVirtualPath);
			                                                      }

			                                                      CurrentNode = ChildNode;

			                                                      return true;
		                                                      });

		CurrentNode->ChildScriptClasses.Add(InClass);
	}
}

TSharedPtr<FScriptClassHierarchyNode> FScriptClassHierarchy::FindNodeByPath(const FName& InPath) const
{
	FString FolderInternalPath = InPath.ToString();

	if (constexpr auto RootFolder = SCRIPT_CLASS_ROOT_INTERNAL_PATH; FolderInternalPath.StartsWith(RootFolder))
	{
		FolderInternalPath = FolderInternalPath.RightChop(strlen(RootFolder));
	}

	if (FolderInternalPath.IsEmpty())
	{
		FolderInternalPath = TEXT("/");
	}

	if (!RootNode.IsValid())
	{
		return TSharedPtr<FScriptClassHierarchyNode>();
	}

	auto CurrentNode = RootNode;

	UUnrealCSharpScriptClassDataSource::EnumerateSubPaths(FolderInternalPath,
	                                                      [this , &CurrentNode](FName SubVirtualPath)
	                                                      {
		                                                      const auto ChildNodeIt = CurrentNode->GetChildrenRef().
			                                                      Find(SubVirtualPath);

		                                                      if (!ChildNodeIt || !ChildNodeIt->IsValid())
		                                                      {
			                                                      return false;
		                                                      }

		                                                      CurrentNode = *ChildNodeIt;

		                                                      return true;
	                                                      });

	return CurrentNode;
}

void FScriptClassHierarchy::GetMatchingFoldersRecurse(const TSharedPtr<FScriptClassHierarchyNode>& InNode,
                                                      TArray<FName>& OutFolders)
{
	for (auto ChildNodeIt : InNode->GetChildrenRef())
	{
		OutFolders.Add(*(SCRIPT_CLASS_ROOT_INTERNAL_PATH / ChildNodeIt.Key.ToString()));

		GetMatchingFoldersRecurse(ChildNodeIt.Value, OutFolders);
	}
}

void FScriptClassHierarchy::GetMatchingClassesRecurse(const TSharedPtr<FScriptClassHierarchyNode>& InNode,
                                                      TArray<UClass*>& OutClasses)
{
	for (auto ScriptClassIt : InNode->GetScriptClasses())
	{
		OutClasses.Add(ScriptClassIt);
	}

	for (auto ChildNodeIt : InNode->GetChildrenRef())
	{
		for (auto ScriptClassIt : ChildNodeIt.Value->GetScriptClasses())
		{
			OutClasses.Add(ScriptClassIt);
		}

		GetMatchingClassesRecurse(ChildNodeIt.Value, OutClasses);
	}
}

TArray<FName> FScriptClassHierarchy::GetMatchingFolders(const FName& InPath, const bool bRecurse) const
{
	const auto CurrentNode = FindNodeByPath(InPath);

	if (!CurrentNode.IsValid())
	{
		return TArray<FName>();
	}

	TArray<FName> MatchingFolders;

	for (auto ChildNodeIt = CurrentNode->GetChildrenRef().CreateConstIterator(); ChildNodeIt; ++ChildNodeIt)
	{
		MatchingFolders.Add(*(SCRIPT_CLASS_ROOT_INTERNAL_PATH / ChildNodeIt->Key.ToString()));

		if (bRecurse)
		{
			GetMatchingFoldersRecurse(ChildNodeIt->Value, MatchingFolders);
		}
	}

	return MatchingFolders;
}

TArray<UClass*> FScriptClassHierarchy::GetMatchingClasses(const FName& InPath, const bool bRecurse) const
{
	const auto CurrentNode = FindNodeByPath(InPath);

	if (!CurrentNode.IsValid())
	{
		return TArray<UClass*>();
	}

	TArray<UClass*> MatchingClasses;

	for (auto ScriptClassIt : CurrentNode->GetScriptClasses())
	{
		MatchingClasses.Add(ScriptClassIt);
	}

	if (bRecurse)
	{
		for (auto ChildNodeIt = CurrentNode->GetChildrenRef().CreateConstIterator(); ChildNodeIt; ++ChildNodeIt)
		{
			GetMatchingClassesRecurse(ChildNodeIt->Value, MatchingClasses);
		}
	}

	return MatchingClasses;
}

void FScriptClassHierarchy::EnumerateLeafNodes(
	const TFunctionRef<void(TSharedPtr<FScriptClassHierarchyNode>&&)>& InCallback)
{
	if (!RootNode.IsValid())
	{
		return;
	}

	EnumerateLeafNodesInternal(RootNode, InCallback);
}

void FScriptClassHierarchy::EnumerateLeafNodesInternal(TSharedPtr<FScriptClassHierarchyNode>& InNode,
                                                       const TFunctionRef<void(TSharedPtr<FScriptClassHierarchyNode>&&)>
                                                       & InCallback)
{
	if (InNode->GetChildrenRef().IsEmpty())
	{
		InCallback(MoveTemp(InNode));
		return;
	}

	for (auto ChildNodeIt : InNode->GetChildrenRef())
	{
		EnumerateLeafNodesInternal(ChildNodeIt.Value, InCallback);
	}
}

void FScriptClassHierarchy::PopulateHierarchy()
{
	RootNode = FScriptClassHierarchyNode::MakeNode(FName(TEXT("/")));

	for (const auto ClassIt : FDynamicClassGenerator::GetDynamicClasses())
	{
		if (ClassIt)
		{
			BuildTreeRecurseFromClass(ClassIt);
		}
	}
}
