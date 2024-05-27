#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FInt64PropertyDescriptor final : public TPrimitivePropertyDescriptor<FInt64Property>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
