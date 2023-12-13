// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnrealCSharpSetting.generated.h"

/**
 * 
 */
UCLASS(config = UnrealCSharpSetting, defaultconfig, meta = (DisplayName = "UnrealCSharpSetting"))
class UNREALCSHARPCORE_API UUnrealCSharpSetting : public UObject
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	static void RegisterSettings();

	static void UnregisterSettings();
#endif

public:
	const TArray<TSubclassOf<UObject>>& GetPreBindClass() const;

private:
	UPROPERTY(Config, EditAnywhere, Category = Bind)
	TArray<TSubclassOf<UObject>> PreBindClass;
};
