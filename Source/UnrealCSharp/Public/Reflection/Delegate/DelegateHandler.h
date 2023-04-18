// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Reflection/Function/FCSharpDelegateDescriptor.h"
#include "DelegateHandler.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCSHARP_API UDelegateHandler final : public UObject
{
	GENERATED_BODY()

public:
	virtual void ProcessEvent(UFunction* Function, void* Parms) override;

	UFUNCTION()
	void CSharpCallBack();

public:
	void Initialize(FScriptDelegate* InScriptDelegate, UFunction* InSignatureFunction);

	void Deinitialize();

public:
	void Bind(MonoObject* InDelegate);

	bool IsBound() const;

	void UnBind();

	void Clear();

	void Execute(MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue) const;

	UObject* GetUObject() const;

	FName GetFunctionName() const;

	UFunction* GetCallBack() const;

private:
	FScriptDelegate* ScriptDelegate;

	FCSharpDelegateDescriptor* DelegateDescriptor;

	MonoObject* Delegate;
};
