#pragma once

#include "Reflection/Property/TCompoundPropertyDescriptor.inl"

class FFieldPathPropertyDescriptor final : public TCompoundPropertyDescriptor<FFieldPathProperty>
{
public:
	using TCompoundPropertyDescriptor::TCompoundPropertyDescriptor;
};
