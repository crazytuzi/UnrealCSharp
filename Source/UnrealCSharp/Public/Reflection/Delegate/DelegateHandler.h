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

	template <typename T>
	void Execute0() const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute0<T>(ScriptDelegate);
				}
			}
		}
	}

	template <typename T>
	auto Execute1() const -> T
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					return DelegateDescriptor->Execute1<T>(ScriptDelegate);
				}
			}
		}

		return {};
	}

	template <typename T>
	void Execute2(uint8* InBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute2<T>(ScriptDelegate, InBuffer);
				}
			}
		}
	}

	template <typename T>
	auto Execute3(uint8* InBuffer) const -> T
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					return DelegateDescriptor->Execute3<T>(ScriptDelegate, InBuffer);
				}
			}
		}

		return {};
	}

	template <typename T>
	void Execute4(MonoObject** OutValue) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute4<T>(ScriptDelegate, OutValue);
				}
			}
		}
	}

	template <typename T>
	void Execute6(MonoObject** OutValue, uint8* InBuffer) const
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					DelegateDescriptor->Execute6<T>(ScriptDelegate, OutValue, InBuffer);
				}
			}
		}
	}

	template <typename T>
	auto Execute7(MonoObject** OutValue, uint8* InBuffer) const -> T
	{
		if (ScriptDelegate != nullptr)
		{
			if (ScriptDelegate->IsBound())
			{
				if (DelegateDescriptor != nullptr)
				{
					return DelegateDescriptor->Execute7<T>(ScriptDelegate, OutValue, InBuffer);
				}
			}
		}

		return {};
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
