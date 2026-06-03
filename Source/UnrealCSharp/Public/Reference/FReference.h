#pragma once

#include "Domain/Script/IManagedHandle.h"
#include "Domain/FDomain.h"

class UNREALCSHARP_API FReference
{
public:
	explicit FReference(const IManagedHandle InManagedHandle):
		ManagedHandle(InManagedHandle)
	{
	}

	virtual ~FReference()
	{
		FDomain::GCHandle_Free(ManagedHandle);

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
