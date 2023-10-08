#pragma once

#include "FReference.h"
#include "Environment/FCSharpEnvironment.h"

template <typename T>
class TDelegateReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~TDelegateReference() override
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<T>(GarbageCollectionHandle);
	}
};
