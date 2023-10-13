#pragma once

#include "FReference.h"

class UNREALCSHARP_API FBindingReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~FBindingReference() override;
};
