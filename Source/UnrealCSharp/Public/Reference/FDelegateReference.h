#pragma once

#include "FReference.h"

class FDelegateReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~FDelegateReference() override;
};
