#pragma once

struct FScriptClassHierarchyNode
{
	static TSharedPtr<FScriptClassHierarchyNode> MakeNode(FName InFileName);

	TMap<FName, TSharedPtr<FScriptClassHierarchyNode>>& GetChildrenRef()
	{
		return Children;
	}

	TSet<UClass*>& GetScriptClasses()
	{
		return ChildScriptClasses;
	}

	FName GetFileName() const
	{
		return FileName;
	}

	FName FileName;

	TSet<UClass*> ChildScriptClasses;

	TMap<FName, TSharedPtr<FScriptClassHierarchyNode>> Children;
};

class FScriptClassHierarchy
{
public:
	FScriptClassHierarchy();

	void BuildTreeRecurseFromClass(UClass* InClass) const;

	TSharedPtr<FScriptClassHierarchyNode> FindNodeByPath(const FName& InPath) const;

	static void GetMatchingFoldersRecurse(const TSharedPtr<FScriptClassHierarchyNode>& InNode,
	                                      TArray<FName>& OutFolders);

	static void GetMatchingClassesRecurse(const TSharedPtr<FScriptClassHierarchyNode>& InNode,
	                                      TArray<UClass*>& OutClasses);

	TArray<FName> GetMatchingFolders(const FName& InPath, const bool bRecurse = false) const;

	TArray<UClass*> GetMatchingClasses(const FName& InPath, const bool bRecurse = false) const;

	void EnumerateLeafNodes(const TFunctionRef<void(TSharedPtr<FScriptClassHierarchyNode>&&)>& InCallback);

private:
	void PopulateHierarchy();

	static void EnumerateLeafNodesInternal(TSharedPtr<FScriptClassHierarchyNode>& InNode,
	                                const TFunctionRef<void(TSharedPtr<FScriptClassHierarchyNode>&&)>& InCallback);

	TSharedPtr<FScriptClassHierarchyNode> RootNode;
};
