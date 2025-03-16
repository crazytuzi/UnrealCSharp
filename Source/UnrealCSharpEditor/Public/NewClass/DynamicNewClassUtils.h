#pragma once

#include "CoreMinimal.h"
#include "AddToProjectConfig.h"
#include "ProjectContent.h"

struct FDynamicNewClassInfo
{
	FDynamicNewClassInfo(const FNewClassInfo& InNewClassInfo);

	FText GetClassName() const;

	FString GetClassNameCPP() const;

	FText GetClassDescription(const bool bFullDescription = true) const;

	bool IsSet() const
	{
		return ClassType != FNewClassInfo::EClassType::UObject || BaseClass;
	}

	FNewClassInfo::EClassType ClassType;

	const UClass* BaseClass;
};

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
