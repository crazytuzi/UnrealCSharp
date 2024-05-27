#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FDoublePropertyDescriptor final : public TPrimitivePropertyDescriptor<FDoubleProperty>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
