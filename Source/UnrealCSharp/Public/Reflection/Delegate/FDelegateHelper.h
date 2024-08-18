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

	template <typename T>
	void Execute0() const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute0<T>();
		}
	}

	template <typename T>
	auto Execute1() const -> T
	{
		if (DelegateHandler != nullptr)
		{
			return DelegateHandler->Execute1<T>();
		}

		return {};
	}

	template <typename T>
	void Execute2(uint8* InBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute2<T>(InBuffer);
		}
	}

	template <typename T>
	auto Execute3(uint8* InBuffer) const -> T
	{
		if (DelegateHandler != nullptr)
		{
			return DelegateHandler->Execute3<T>(InBuffer);
		}

		return {};
	}

	template <typename T>
	void Execute4(MonoObject** OutValue) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute4<T>(OutValue);
		}
	}

	template <typename T>
	void Execute6(MonoObject** OutValue, uint8* InBuffer) const
	{
		if (DelegateHandler != nullptr)
		{
			DelegateHandler->Execute6<T>(OutValue, InBuffer);
		}
	}

	template <typename T>
	auto Execute7(MonoObject** OutValue, uint8* InBuffer) const -> T
	{
		if (DelegateHandler != nullptr)
		{
			return DelegateHandler->Execute7<T>(OutValue, InBuffer);
		}

		return {};
	}

	UObject* GetUObject() const;

	FName GetFunctionName() const;

private:
	TWeakObjectPtr<UDelegateHandler> DelegateHandler;
};
