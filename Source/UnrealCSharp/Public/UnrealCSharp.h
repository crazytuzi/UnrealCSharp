// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Listener/FUObjectListener.h"
#include "Modules/ModuleManager.h"

class FUnrealCSharpModule final : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

public:
	void OnUnrealCSharpCoreModuleActive();

	void OnUnrealCSharpCoreModuleInActive();

private:
	FDelegateHandle OnUnrealCSharpCoreModuleActiveDelegateHandle;

	FDelegateHandle OnUnrealCSharpCoreModuleInActiveDelegateHandle;

	FUObjectListener UObjectListener;
};
