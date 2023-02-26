#pragma once

#include "FReference.h"

class FContainerReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~FContainerReference() override;
};
