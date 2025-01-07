#pragma once

#include "FReference.h"
#include "Environment/FCSharpEnvironment.h"

class FStructReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~FStructReference() override
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveStructReference(GarbageCollectionHandle);
	}
};
