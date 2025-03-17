#pragma once

#include "FReference.h"
#include "Environment/FCSharpEnvironment.h"

class UNREALCSHARP_API FBindingReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~FBindingReference() override
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveBindingReference(GarbageCollectionHandle);
	}
};
