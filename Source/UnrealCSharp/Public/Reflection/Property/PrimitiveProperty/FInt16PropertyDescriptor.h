#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FInt16PropertyDescriptor final : public TPrimitivePropertyDescriptor<FInt16Property>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
