#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FFieldPathPropertyDescriptor final : public TCompoundPropertyDescriptor<FFieldPathProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, bool bIsCopy) const override;

	virtual void Set(void* Src, void* Dest) const override;
};
