#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FMulticastDelegatePropertyDescriptor : public TCompoundPropertyDescriptor<FMulticastDelegateProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, std::true_type) const override;

	virtual void Get(void* Src, void** Dest, std::false_type) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

protected:
	virtual const FMulticastScriptDelegate* GetMulticastDelegate(void* InAddress) const;

private:
	MonoObject* NewRef(void* InAddress) const;

	MonoObject* NewWeakRef(void* InAddress) const;
};
