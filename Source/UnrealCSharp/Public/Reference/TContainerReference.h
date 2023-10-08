#pragma once

#include "FReference.h"
#include "Environment/FCSharpEnvironment.h"

template <typename T>
class TContainerReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~TContainerReference() override
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<T>(GarbageCollectionHandle);
	}
};
