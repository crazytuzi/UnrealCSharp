// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DynamicScriptStruct.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCSHARPCORE_API UDynamicScriptStruct : public UScriptStruct
{
	GENERATED_BODY()

public:
	FGuid Guid;

	virtual FGuid GetCustomGuid() const override;
};
