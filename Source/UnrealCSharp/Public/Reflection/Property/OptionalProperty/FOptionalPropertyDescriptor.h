#pragma once

#include "Reflection/Property/FCompoundPropertyDescriptor.h"
#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
class FOptionalPropertyDescriptor final : public FCompoundPropertyDescriptor
{
public:
	using FCompoundPropertyDescriptor::FCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* NewWeakRef(void* InAddress) const;
};
#endif
