#pragma once

#include "FDelegateBaseHelper.h"
#include "MulticastDelegateHandler.h"

class FMulticastDelegateHelper final : public FDelegateBaseHelper
{
public:
	FMulticastDelegateHelper();

	FMulticastDelegateHelper(FMulticastScriptDelegate* InMulticastDelegate, UFunction* InSignatureFunction);

	virtual ~FMulticastDelegateHelper() override;

public:
	void Initialize(FMulticastScriptDelegate* InMulticastDelegate, UFunction* InSignatureFunction);

	void Deinitialize();

public:
	bool IsBound() const;

	bool Contains(UObject* InObject, MonoMethod* InMonoMethod) const;

	void Add(UObject* InObject, MonoMethod* InMonoMethod) const;

	void AddUnique(UObject* InObject, MonoMethod* InMonoMethod) const;

	void Remove(UObject* InObject, MonoMethod* InMonoMethod) const;

	void RemoveAll(UObject* InObject) const;

	void Clear() const;

	MonoObject* Broadcast(MonoObject** OutValue, MonoArray* InValue) const;

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UMulticastDelegateHandler> MulticastDelegateHandler;
};
