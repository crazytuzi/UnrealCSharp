// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FDelegateWrapper.h"
#include "Reflection/Function/FCSharpDelegateDescriptor.h"
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

	bool Contains(UObject* InObject, MonoObject* InMonoDelegate) const;

	void Add(UObject* InObject, MonoObject* InMonoDelegate);

	void AddUnique(UObject* InObject, MonoObject* InMonoDelegate);

	void Remove(UObject* InObject, MonoObject* InMonoDelegate);

	void RemoveAll(UObject* InObject);

	void Clear();

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast0() const
	{
		if (MulticastScriptDelegate != nullptr)
		{
			if (MulticastScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Broadcast0<ReturnType>(MulticastScriptDelegate);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast2(uint8* InBuffer) const
	{
		if (MulticastScriptDelegate != nullptr)
		{
			if (MulticastScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Broadcast2<ReturnType>(MulticastScriptDelegate, InBuffer);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast4(uint8* OutBuffer) const
	{
		if (MulticastScriptDelegate != nullptr)
		{
			if (MulticastScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Broadcast4<ReturnType>(MulticastScriptDelegate, OutBuffer);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast6(uint8* InBuffer, uint8* OutBuffer) const
	{
		if (MulticastScriptDelegate != nullptr)
		{
			if (MulticastScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Broadcast6<ReturnType>(MulticastScriptDelegate, InBuffer, OutBuffer);
				}
			}
		}
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

	UFunction* GetCallBack() const;

private:
	bool bNeedFree;

	FMulticastScriptDelegate* MulticastScriptDelegate;

	FCSharpDelegateDescriptor* DelegateDescriptor;

	FScriptDelegate ScriptDelegate;

	TArray<FDelegateWrapper> DelegateWrappers;
};
