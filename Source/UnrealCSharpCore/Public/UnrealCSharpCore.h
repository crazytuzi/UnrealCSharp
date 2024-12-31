// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Listener/FEngineListener.h"
#include "Modules/ModuleManager.h"

class UNREALCSHARPCORE_API FUnrealCSharpCoreModule final : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:
	static FORCEINLINE FUnrealCSharpCoreModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FUnrealCSharpCoreModule>("UnrealCSharpCore");
	}

public:
	void SetActive(bool InbIsActive);

private:
	FEngineListener EngineListener;

	bool bIsActive = false;
};
