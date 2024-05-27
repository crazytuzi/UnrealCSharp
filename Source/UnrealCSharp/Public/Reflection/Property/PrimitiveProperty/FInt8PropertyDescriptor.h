#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FInt8PropertyDescriptor final : public TPrimitivePropertyDescriptor<FInt8Property>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
