// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSharpFunction.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCSHARP_API UCSharpFunction : public UFunction
{
	GENERATED_BODY()

public:
	DECLARE_FUNCTION(execCallCSharp);
};
