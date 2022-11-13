#pragma once

#include "MulticastDelegateHandler.h"

class FMulticastDelegateHelper
{
public:
	FMulticastDelegateHelper(FMulticastScriptDelegate* InMulticastDelegate, UFunction* InSignatureFunction);

	~FMulticastDelegateHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	bool IsBound() const;

	bool Contains(MonoObject* InMulticastDelegate) const;

	void Add(MonoObject* InMulticastDelegate) const;

	void AddUnique(MonoObject* InMulticastDelegate) const;

	void Remove(MonoObject* InMulticastDelegate) const;

	void RemoveAll(MonoObject* InMonoObject) const;

	void Clear() const;

	void Broadcast(MonoObject** OutValue, MonoArray* InValue) const;

private:
	UMulticastDelegateHandler* MulticastDelegateHandler;
};
