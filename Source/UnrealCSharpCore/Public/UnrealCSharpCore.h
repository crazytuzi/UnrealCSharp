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
	void Activate();

	void Deactivate();

	void MarkOutdated();

	bool IsLoaded() const;

	bool IsActive() const;

	bool IsOutdated() const;

private:
	enum class EState : uint8
	{
		Inactive,
		Active,
		Outdated
	};

	FEngineListener EngineListener;

	EState State = EState::Inactive;
};
