#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FBytePropertyDescriptor final : public TPrimitivePropertyDescriptor<FByteProperty>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
