#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FUInt64PropertyDescriptor final : public TPrimitivePropertyDescriptor<FUInt64Property>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
