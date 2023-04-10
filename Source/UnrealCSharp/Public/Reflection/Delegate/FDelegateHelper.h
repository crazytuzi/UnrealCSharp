#pragma once

#include "FDelegateBaseHelper.h"
#include "DelegateHandler.h"

class FDelegateHelper final : public FDelegateBaseHelper
{
public:
	FDelegateHelper(FScriptDelegate* InDelegate, UFunction* InSignatureFunction);

	virtual ~FDelegateHelper() override;

public:
	void Initialize();

	void Deinitialize();

public:
	void Bind(MonoObject* InDelegate) const;

	bool IsBound() const;

	void UnBind() const;

	void Clear() const;

	void Execute(MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue) const;

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	UDelegateHandler* DelegateHandler;
};
