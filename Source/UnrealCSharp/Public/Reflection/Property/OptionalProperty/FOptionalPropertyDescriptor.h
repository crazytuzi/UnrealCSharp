#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#endif

#if UE_F_OPTIONAL_PROPERTY
class FOptionalPropertyDescriptor final : public TCompoundPropertyDescriptor<FOptionalProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, std::true_type) const override;

	virtual void Get(void* Src, void** Dest, std::false_type) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* NewWeakRef(void* InAddress, bool bIsCopy) const;
};
#endif
