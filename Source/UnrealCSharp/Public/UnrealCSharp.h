// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Listener/FEngineListener.h"
#include "Listener/FUObjectListener.h"
#include "Modules/ModuleManager.h"

class FUnrealCSharpModule final: public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

public:
	static FORCEINLINE FUnrealCSharpModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FUnrealCSharpModule>("UnrealCSharp");
	}

public:
	bool GetActive() const;

	void SetActive(bool InbIsActive);

private:
	FUObjectListener UObjectListener;

	FEngineListener EngineListener;

	bool bIsActive = false;
};
