#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FUInt32PropertyDescriptor final : public TPrimitivePropertyDescriptor<FUInt32Property>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
