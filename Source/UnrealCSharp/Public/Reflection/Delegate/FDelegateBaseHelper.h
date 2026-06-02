#pragma once

class FDelegateBaseHelper
{
public:
	explicit FDelegateBaseHelper(void* InAddress = nullptr):
		Address(InAddress)
	{
	}

	virtual ~FDelegateBaseHelper() = default;

	void* GetAddress() const
	{
		return Address;
	}

protected:
	void SetAddress(void* InAddress)
	{
		Address = InAddress;
	}

private:
	void* Address;
};
