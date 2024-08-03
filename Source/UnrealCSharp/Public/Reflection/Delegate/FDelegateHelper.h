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

	MonoObject* Execute(MonoObject** OutValue, MonoArray* InValue) const;

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UDelegateHandler> DelegateHandler;
};
