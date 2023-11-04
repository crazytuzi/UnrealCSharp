// Fill out your copyright notice in the Description page of Project Settings.


#include "Dynamic/CSharpBlueprint.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"

#if WITH_EDITOR
UClass* UCSharpBlueprint::GetBlueprintClass() const
{
	return UCSharpBlueprintGeneratedClass::StaticClass();
}
#endif
