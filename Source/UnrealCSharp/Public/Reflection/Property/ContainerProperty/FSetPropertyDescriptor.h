#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FSetPropertyDescriptor final : public TCompoundPropertyDescriptor<FSetProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, bool bIsCopy) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* NewRef(void* InAddress) const;

	MonoObject* NewWeakRef(void* InAddress, bool bIsCopy) const;
};
