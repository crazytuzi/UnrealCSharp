#pragma once

#include "CoreMacro/BufferMacro.h"
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

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast0() const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast0<ReturnType>();
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast2(IN_BUFFER_SIGNATURE) const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast2<ReturnType>(IN_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast4(OUT_BUFFER_SIGNATURE) const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast4<ReturnType>(OUT_BUFFER);
		}
	}

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast6(IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const
	{
		if (MulticastDelegateHandler != nullptr)
		{
			MulticastDelegateHandler->Broadcast6<ReturnType>(IN_BUFFER, OUT_BUFFER);
		}
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UMulticastDelegateHandler> MulticastDelegateHandler;
};
