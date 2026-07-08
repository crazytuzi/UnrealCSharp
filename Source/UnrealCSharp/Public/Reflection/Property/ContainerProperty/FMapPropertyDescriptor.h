#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FMapPropertyDescriptor final : public TCompoundPropertyDescriptor<FMapProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, std::true_type) const override;

	virtual void Get(void* Src, void** Dest, std::false_type) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	IManagedHandle NewRef(void* InAddress) const;

	IManagedHandle NewWeakRef(void* InAddress, bool bIsCopy) const;
};
