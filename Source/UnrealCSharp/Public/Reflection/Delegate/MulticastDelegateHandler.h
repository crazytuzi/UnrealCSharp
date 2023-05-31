// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "MulticastDelegateHandler.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCSHARP_API UMulticastDelegateHandler final : public UObject
{
	GENERATED_BODY()

public:
	virtual void ProcessEvent(UFunction* Function, void* Parms) override;

	UFUNCTION()
	void CSharpCallBack();

public:
	void Initialize(FMulticastScriptDelegate* InMulticastScriptDelegate, UFunction* InSignatureFunction);

	void Deinitialize();

public:
	bool IsBound() const;

	bool Contains(MonoObject* InMulticastDelegate) const;

	void Add(MonoObject* InMulticastDelegate);

	void AddUnique(MonoObject* InMulticastDelegate);

	void Remove(MonoObject* InMulticastDelegate);

	void RemoveAll(MonoObject* InObject);

	void Clear();

	void Broadcast(MonoObject** OutValue, MonoArray* InValue) const;

private:
	FMulticastScriptDelegate* MulticastScriptDelegate;

	FCSharpDelegateDescriptor* DelegateDescriptor;

	FScriptDelegate ScriptDelegate;

	TArray<FGarbageCollectionHandle> DelegateGarbageCollectionHandles;
};
