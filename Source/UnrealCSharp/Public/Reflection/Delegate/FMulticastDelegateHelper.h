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

	template <typename T>
	void Broadcast0() const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast0<T>();
		}
	}

	template <typename T>
	void Broadcast2(uint8* InBuffer) const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast2<T>(InBuffer);
		}
	}

	template <typename T>
	void Broadcast4(MonoObject** OutValue) const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast4<T>(OutValue);
		}
	}

	template <typename T>
	void Broadcast6(MonoObject** OutValue, uint8* InBuffer) const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast6<T>(OutValue, InBuffer);
		}
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UMulticastDelegateHandler> MulticastDelegateHandler;
};
