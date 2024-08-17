// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssemblyLoader.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCSHARPCORE_API UAssemblyLoader : public UObject
{
	GENERATED_BODY()

public:
	virtual TArray<uint8> Load(const FString& InAssemblyName);
};
