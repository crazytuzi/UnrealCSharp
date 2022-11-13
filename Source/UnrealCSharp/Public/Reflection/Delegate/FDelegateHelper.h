#pragma once

#include "DelegateHandler.h"

class FDelegateHelper
{
public:
	FDelegateHelper(FScriptDelegate* InDelegate, UFunction* InSignatureFunction);

	~FDelegateHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	void Bind(MonoObject* InDelegate) const;

	bool IsBound() const;

	void UnBind() const;

	void Clear() const;

	void Execute(MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue) const;

private:
	UDelegateHandler* DelegateHandler;
};
