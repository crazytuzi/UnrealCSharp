#pragma once

#include "Reflection/Property/TPrimitivePropertyDescriptor.inl"

class FIntPropertyDescriptor final : public TPrimitivePropertyDescriptor<FIntProperty>
{
public:
	using TPrimitivePropertyDescriptor::TPrimitivePropertyDescriptor;
};
