#pragma once

#include "CoreMinimal.h"

class UToolMenu;

class FDynamicNewClassContextMenu
{
public:
	DECLARE_DELEGATE_OneParam(FOnOpenNewDynamicClassRequested, const FName&);

	static void MakeContextMenu(
		UToolMenu* InMenu,
		const TArray<FName>& InSelectedClassPaths,
		const FOnOpenNewDynamicClassRequested& InOnOpenNewDynamicClassRequested
	);

private:
	static void ExecuteNewClass(const FName InPath, FOnOpenNewDynamicClassRequested InOnOpenNewDynamicClassRequested);
};
