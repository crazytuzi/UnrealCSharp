#pragma once

#include "Domain/Script/IManagedHandle.h"

class UNREALCSHARP_API FReference
{
public:
	explicit FReference(const IManagedHandle InManagedHandle):
		ManagedHandle(InManagedHandle)
	{
	}

	virtual ~FReference()
	{
		ManagedHandle = IManagedHandle{};
	}

public:
	explicit operator IManagedHandle() const
	{
		return ManagedHandle;
	}

protected:
	IManagedHandle ManagedHandle;
};
