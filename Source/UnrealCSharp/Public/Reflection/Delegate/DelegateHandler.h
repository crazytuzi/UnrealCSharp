// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FDelegateWrapper.h"
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
	void Bind(UObject* InObject, MonoMethod* InMonoMethod);

	bool IsBound() const;

	void UnBind() const;

	void Clear() const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute0() const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute0<ReturnType>(ScriptDelegate);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute1(uint8* ReturnBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute1<ReturnType>(ScriptDelegate, ReturnBuffer);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute2(uint8* InBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute2<ReturnType>(ScriptDelegate, InBuffer);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute3(uint8* InBuffer, uint8* ReturnBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute3<ReturnType>(ScriptDelegate, InBuffer, ReturnBuffer);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute4(MonoObject** OutValue) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute4<ReturnType>(ScriptDelegate, OutValue);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute6(MonoObject** OutValue, uint8* InBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute6<ReturnType>(ScriptDelegate, OutValue, InBuffer);
				}
			}
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute7(MonoObject** OutValue, uint8* InBuffer, uint8* ReturnBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute7<ReturnType>(ScriptDelegate, OutValue, InBuffer, ReturnBuffer);
				}
			}
		}
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

	UFunction* GetCallBack() const;

private:
	bool bNeedFree;

	FScriptDelegate* ScriptDelegate;

	FCSharpDelegateDescriptor* DelegateDescriptor;

	FDelegateWrapper DelegateWrapper;
};
