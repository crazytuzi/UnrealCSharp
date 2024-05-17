#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FUInt16PropertyDescriptor final : public TPrimitivePropertyDescriptor<FUInt16Property>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
