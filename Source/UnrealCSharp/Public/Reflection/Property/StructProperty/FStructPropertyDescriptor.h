#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FStructPropertyDescriptor final : public TCompoundPropertyDescriptor<FStructProperty>
{
public:
	explicit FStructPropertyDescriptor(FStructProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest, FPropertyArgument::FMember) const override;

	virtual void Get(void* Src, void** Dest, FPropertyArgument::FReturn) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const override;

private:
	IManagedHandle NewRef(void* InAddress) const;
};
