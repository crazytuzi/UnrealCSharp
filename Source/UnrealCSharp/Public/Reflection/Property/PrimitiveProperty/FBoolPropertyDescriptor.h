#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FBoolPropertyDescriptor final : public TPrimitivePropertyDescriptor<FBoolProperty>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;

	virtual void Set(void* Src, void* Dest) const override;
};
