#pragma once

#include "CoreMacro/BufferMacro.h"
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
	void Execute1(RETURN_BUFFER_SIGNATURE) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute1<ReturnType>(RETURN_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute2(IN_BUFFER_SIGNATURE) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute2<ReturnType>(IN_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute3(IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute3<ReturnType>(IN_BUFFER, RETURN_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute4(OUT_BUFFER_SIGNATURE) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute4<ReturnType>(OUT_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute6(IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute6<ReturnType>(IN_BUFFER, OUT_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute7(IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute7<ReturnType>(IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
		}
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UDelegateHandler> DelegateHandler;
};
