#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FSetPropertyDescriptor final : public TCompoundPropertyDescriptor<FSetProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, std::true_type) const override;

	virtual void Get(void* Src, void** Dest, std::false_type) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	IManagedObject NewRef(void* InAddress) const;

	IManagedObject NewWeakRef(void* InAddress, bool bIsCopy) const;
};
