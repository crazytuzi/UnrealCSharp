#pragma once

struct FDynamicHierarchyNode
{
	TSet<UClass*>& GetClasses()
	{
		return Classes;
	}

	TMap<FName, TSharedPtr<FDynamicHierarchyNode>>& GetChildren()
	{
		return Children;
	}

	TSet<UClass*> Classes;

	TMap<FName, TSharedPtr<FDynamicHierarchyNode>> Children;
};

class FDynamicHierarchy
{
public:
	FDynamicHierarchy();

	TSharedPtr<FDynamicHierarchyNode> FindNode(const FName& InPath) const;

	static void GetMatchingFolders(const TSharedPtr<FDynamicHierarchyNode>& InNode, TArray<FName>& OutFolders);

	static void GetMatchingClasses(const TSharedPtr<FDynamicHierarchyNode>& InNode, TArray<UClass*>& OutClasses);

	TArray<FName> GetMatchingFolders(const FName& InPath, const bool bRecurse = false) const;

	TArray<UClass*> GetMatchingClasses(const FName& InPath, const bool bRecurse = false) const;

	static FString ConvertInternalPathToFileSystemPath(const FString& InInternalPath);

private:
	static bool EnumeratePath(const FString& InPath, const TFunctionRef<bool(const FName&)>& InCallback);

	void AddClass(UClass* InClass) const;

	void PopulateHierarchy();

private:
	TSharedPtr<FDynamicHierarchyNode> Root;
};
