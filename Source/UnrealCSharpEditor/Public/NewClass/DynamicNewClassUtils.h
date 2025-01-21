#pragma once

#include "CoreMinimal.h"

struct FProjectContextInfo
{
	FProjectContextInfo(const FString& InProjectName, const FString& InProjectSourcePath)
		: ProjectName(InProjectName)
		  , ProjectSourcePath(InProjectSourcePath)
	{
	}

	FProjectContextInfo(FString&& InProjectName, FString&& InProjectSourcePath)
		: ProjectName(MoveTemp(InProjectName)),
		  ProjectSourcePath(MoveTemp(InProjectSourcePath))
	{
	}

	FString ProjectName;

	FString ProjectSourcePath;
};

class FDynamicNewClassUtils
{
public:
	static void OpenAddDynamicClassToProjectDialog(const FString& InitialPath);

	static TArray<FProjectContextInfo> GetCurrentProjectsInfo();

	static void GetDynamicClassContent(const UClass* InParentClass, const FString& InNewClassName, FString& OutContent);

	static UClass* GetAncestorClass(const UClass* InParentClass);

	static void AddNamespaceIfUnique(FString& OutContent, const FString& InNamespace);

	static FString GetAssetGeneratedClassName(const FAssetData& InAssetData);
};
