#pragma once

class FDelegateBaseHelper
{
public:
	explicit FDelegateBaseHelper(void* InAddress):
		Address(InAddress)
	{
	}

	virtual ~FDelegateBaseHelper() = default;

public:
	void* GetAddress() const
	{
		return Address;
	}

private:
	void* Address;
};
