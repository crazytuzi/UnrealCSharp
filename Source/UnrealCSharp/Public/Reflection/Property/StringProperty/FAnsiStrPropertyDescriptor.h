#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"
#include "UEVersion.h"

#if UE_F_ANSI_STR_PROPERTY
class FAnsiStrPropertyDescriptor final : public TCompoundPropertyDescriptor<FAnsiStrProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest, std::true_type) const override;

	virtual void Get(void* Src, void** Dest, std::false_type) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const override;
};
#endif
