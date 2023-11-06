// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Blueprint.h"
#include "CSharpBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCSHARPCORE_API UCSharpBlueprint : public UBlueprint
{
	GENERATED_BODY()

#if WITH_EDITOR
	virtual UClass* GetBlueprintClass() const override;
#endif
};
