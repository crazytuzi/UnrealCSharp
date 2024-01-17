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

	bool Contains(MonoObject* InMulticastDelegate) const;

	void Add(MonoObject* InMulticastDelegate) const;

	void AddUnique(MonoObject* InMulticastDelegate) const;

	void Remove(MonoObject* InMulticastDelegate) const;

	void RemoveAll(MonoObject* InObject) const;

	void Clear() const;

	MonoObject* Broadcast(MonoObject** OutValue, MonoArray* InValue) const;

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UMulticastDelegateHandler> MulticastDelegateHandler;
};
