#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FFloatPropertyDescriptor final : public TPrimitivePropertyDescriptor<FFloatProperty>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
