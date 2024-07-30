#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FObjectPropertyDescriptor final : public TCompoundPropertyDescriptor<FObjectProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, bool bIsCopy) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const override;
};
