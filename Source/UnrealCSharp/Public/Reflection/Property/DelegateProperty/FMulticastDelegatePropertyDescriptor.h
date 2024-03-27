#pragma once

#include "Reflection/Property/FCompoundPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FMulticastDelegatePropertyDescriptor : public FCompoundPropertyDescriptor
{
public:
	using FCompoundPropertyDescriptor::FCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

protected:
	virtual const FMulticastScriptDelegate* GetMulticastDelegate(void* InAddress) const;

private:
	MonoObject* NewRef(void* InAddress) const;

	MonoObject* NewWeakRef(void* InAddress) const;
};
