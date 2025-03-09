﻿#include "ContentBrowser/DynamicHierarchy.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Dynamic/FDynamicGenerator.h"

FDynamicHierarchy::FDynamicHierarchy()
{
	PopulateHierarchy();
}

TSharedPtr<FDynamicHierarchyNode> FDynamicHierarchy::FindNode(const FName& InPath) const
{
	if (!Root.IsValid())
	{
		return MakeShared<FDynamicHierarchyNode>();
	}

	auto Path = InPath.ToString();

	if (Path.StartsWith(DYNAMIC_ROOT_INTERNAL_PATH))
	{
		Path = Path.RightChop(DYNAMIC_ROOT_INTERNAL_PATH.Len());
	}

	if (Path.IsEmpty())
	{
		Path = TEXT("/");
	}

	auto Node = Root;

	EnumeratePath(Path,
	              [&Node](const FName& InInternalPath)
	              {
		              const auto Child = Node->GetChildren().Find(InInternalPath);

		              if (!Child)
		              {
			              return false;
		              }

		              Node = *Child;

		              return true;
	              });

	return Node;
}

void FDynamicHierarchy::GetMatchingFolders(const TSharedPtr<FDynamicHierarchyNode>& InNode, TArray<FName>& OutFolders)
{
	for (const auto& [Key, Value] : InNode->GetChildren())
	{
		OutFolders.Add(*(DYNAMIC_ROOT_INTERNAL_PATH / Key.ToString()));

		GetMatchingFolders(Value, OutFolders);
	}
}

void FDynamicHierarchy::GetMatchingClasses(const TSharedPtr<FDynamicHierarchyNode>& InNode, TArray<UClass*>& OutClasses)
{
	for (const auto& Class : InNode->GetClasses())
	{
		OutClasses.Add(Class);
	}

	for (const auto& [PLACEHOLDER, Value] : InNode->GetChildren())
	{
		for (const auto& Class : Value->GetClasses())
		{
			OutClasses.Add(Class);
		}

		GetMatchingClasses(Value, OutClasses);
	}
}

TArray<FName> FDynamicHierarchy::GetMatchingFolders(const FName& InPath, const bool bRecurse) const
{
	const auto& Node = FindNode(InPath);

	if (!Node.IsValid())
	{
		return TArray<FName>();
	}

	TArray<FName> MatchingFolders;

	for (const auto& [Key, Value] : Node->GetChildren())
	{
		MatchingFolders.Add(*(DYNAMIC_ROOT_INTERNAL_PATH / Key.ToString()));

		if (bRecurse)
		{
			GetMatchingFolders(Value, MatchingFolders);
		}
	}

	return MatchingFolders;
}

TArray<UClass*> FDynamicHierarchy::GetMatchingClasses(const FName& InPath, const bool bRecurse) const
{
	TArray<UClass*> MatchingClasses;

	const auto Node = FindNode(InPath);

	if (!Node.IsValid())
	{
		return MatchingClasses;
	}

	for (const auto& Class : Node->GetClasses())
	{
		MatchingClasses.Add(Class);
	}

	if (bRecurse)
	{
		for (const auto& [PLACEHOLDER, Value] : Node->GetChildren())
		{
			GetMatchingClasses(Value, MatchingClasses);
		}
	}

	return MatchingClasses;
}

void FDynamicHierarchy::TryConvertInternalPathToFileSystemPath(const FString& InSelectedInternalPath,
                                                               FString& OutFileSystemPath)
{
	FString SelectedDirectoryPath = InSelectedInternalPath;

	if (SelectedDirectoryPath.IsEmpty() || !SelectedDirectoryPath.StartsWith(TEXT("/")))
	{
		return;
	}

	const int32 SecondSlashIndex = SelectedDirectoryPath.Find(
		TEXT("/"), ESearchCase::IgnoreCase, ESearchDir::FromStart, 1);

	SelectedDirectoryPath = SecondSlashIndex != INDEX_NONE
		                        ? SelectedDirectoryPath.RightChop(SecondSlashIndex)
		                        : TEXT("");

	if (SelectedDirectoryPath.IsEmpty())
	{
		return;
	}

	OutFileSystemPath = FUnrealCSharpFunctionLibrary::GetFullScriptDirectory() / SelectedDirectoryPath;
}

bool FDynamicHierarchy::EnumeratePath(const FString& InPath, const TFunctionRef<bool(const FName&)>& InCallback)
{
	const auto Path = *InPath;

	auto PathStart = Path + 1;

	const auto PathEnd = Path + InPath.Len();

	for (;;)
	{
		if (PathStart >= PathEnd || *PathStart == TEXT('/'))
		{
			if (const FName SubPath(UE_PTRDIFF_TO_INT32(PathStart - Path), Path);
				!SubPath.IsNone())
			{
				if (!InCallback(SubPath))
				{
					return false;
				}
			}
		}

		if (PathStart >= PathEnd)
		{
			break;
		}

		++PathStart;
	}

	return true;
}

void FDynamicHierarchy::AddClass(UClass* InClass) const
{
	if (InClass == nullptr)
	{
		return;
	}

	if (const auto& Path = FPaths::GetPath(FDynamicGenerator::GetDynamicNormalizeFile(InClass));
		FUnrealCSharpFunctionLibrary::IsRootPath(Path))
	{
		const auto& RelativePath = Path.RightChop(
			FUnrealCSharpFunctionLibrary::GetFullScriptDirectory().Len());

		auto Node = Root;

		EnumeratePath(RelativePath,
		              [&Node](const FName& InInternalPath)
		              {
			              auto& Child = Node->GetChildren().FindOrAdd(InInternalPath);

			              if (!Child.IsValid())
			              {
				              Child = MakeShared<FDynamicHierarchyNode>();
			              }

			              Node = Child;

			              return true;
		              });

		Node->GetClasses().Add(InClass);
	}
}

void FDynamicHierarchy::PopulateHierarchy()
{
	Root = MakeShared<FDynamicHierarchyNode>();

	for (const auto& Class : FDynamicClassGenerator::GetDynamicClasses())
	{
		AddClass(Class);
	}
}
