#pragma once

#include "CoreMinimal.h"
#include "ProjectContent.h"

class FDynamicNewClassUtils
{
public:
	static void OpenAddDynamicClassToProjectDialog(const FString& InInitialPath);

	static TArray<FProjectContent> GetProjectContent();

	static void GetDynamicClassContent(const UClass* InParentClass, const FString& InNewClassName, FString& OutContent);

	static FString GetAssetGeneratedClassName(const FAssetData& InAssetData);

private:
	static UClass* GetAncestorClass(const UClass* InClass);

	static void AddNamespace(const FString& InNamespace, FString& OutContent);
};
