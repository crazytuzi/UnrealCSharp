#pragma once

#include "FDelegateBaseHelper.h"
#include "DelegateHandler.h"

class FDelegateHelper final : public FDelegateBaseHelper
{
public:
	typedef UDelegateHandler UHandlerType;

public:
	FDelegateHelper();

	FDelegateHelper(FScriptDelegate* InDelegate, UFunction* InSignatureFunction);

	virtual ~FDelegateHelper() override;

public:
	void Initialize(FScriptDelegate* InDelegate, UFunction* InSignatureFunction);

	void Deinitialize();

public:
	void Bind(UObject* InObject, MonoMethod* InMonoMethod) const;

	bool IsBound() const;

	void UnBind() const;

	void Clear() const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute0() const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute0<ReturnType>();
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute1(uint8* ReturnBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute1<ReturnType>(ReturnBuffer);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute2(uint8* InBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute2<ReturnType>(InBuffer);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute3(uint8* InBuffer, uint8* ReturnBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute3<ReturnType>(InBuffer, ReturnBuffer);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute4(MonoObject** OutValue) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute4<ReturnType>(OutValue);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute6(MonoObject** OutValue, uint8* InBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute6<ReturnType>(OutValue, InBuffer);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute7(MonoObject** OutValue, uint8* InBuffer, uint8* ReturnBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute7<ReturnType>(OutValue, InBuffer, ReturnBuffer);
		}
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UDelegateHandler> DelegateHandler;
};
