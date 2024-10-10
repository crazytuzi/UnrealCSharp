#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FEnumPropertyDescriptor final : public TPrimitivePropertyDescriptor<FEnumProperty>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, std::true_type) const override;

	virtual void Get(void* Src, void** Dest, std::false_type) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual void DestroyValue(void* Dest) const override;
};
