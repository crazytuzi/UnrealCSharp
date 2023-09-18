#pragma once

#include "FReference.h"

class FStructReference final : public FReference
{
public:
	using FReference::FReference;

public:
	virtual ~FStructReference() override;
};
